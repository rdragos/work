#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <iostream>

void *shared_malloc(int len) {
    void *addr = mmap
        (   0, len, 
            PROT_READ| PROT_WRITE,
            MAP_ANONYMOUS| MAP_SHARED,
            -1,0
        );
    if (addr == MAP_FAILED) {
        printf("mmap failed");
    }   
    return addr;
}

void shared_free(void *p, int len) {
    munmap(p, len);
}

void merge(int *V, int left, int mid, int right) {
    int i = left, j = mid + 1, cnt = 0;
    int *temp = (int *)malloc(sizeof(int) * (right - left + 1) );
    
    for (; i <= mid && j <= right; ) {
        if (V[i] <= V[j]) {
            temp[cnt++] = V[i];
            ++i;
        } else {
            temp[cnt++] = V[j];
            ++j;
        }
    }
    for (; i <= mid; ++i) {
        temp[cnt++] = V[i];
    }
    for(; j <= right; ++j) {
        temp[cnt++] = V[j];
    }
    for (i = left; i <= right; ++i) {
        V[i] = temp[i - left];
    }
    free(temp); 
}
void merge_sort(int *V, int left, int right) {
    if (left >= right) {
        return ;
    }

    int mid = (left + right) / 2;

    pid_t leftpid = -1, rightpid = -1;
    leftpid = fork();

    if (leftpid < 0) {
        perror("fork");
        exit(1);
    }
    if (leftpid == 0) {
        merge_sort(V, left, mid);
    } else {
        rightpid = fork();
        if (rightpid < 0) {
            perror("fork");
            exit(1);
        } else {
            merge_sort(V, mid + 1, right);
        }
    }
    
    waitpid(leftpid, NULL, 0);
    waitpid(rightpid, NULL, 0);
    //merge the result
    merge(V, left, mid, right);
} 


int main(int argc, char *argv[]) {
    
    int N = argc - 1;
    int *V = (int *)shared_malloc(sizeof(int) * N);
    int i;

    for (i = 0; i < N; ++i) {
        V[i] = atoi(argv[i + 1]);
    }
    
    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        exit(1);
    }
    if (child == 0) {
        merge_sort(V, 0, N - 1);
        exit(0);
    } else {
        waitpid(child, NULL, 0);
        printf("Sirul sortat\n");
        for (i = 0; i < N; ++i) {
            printf("%d ", V[i]);
        }
        shared_free(V, sizeof(int) * N);
    }
    return 0;
}

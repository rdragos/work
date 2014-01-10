#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int n, m;
FILE *ptr_out1, *ptr_out2, *ptr_out3;


int offset(int i, int j, int n, int m) {
    return (sizeof(int) * 2) + ((i * m + j) * sizeof(double)) ; 
}
void new_matrix(int _n, int _m, FILE *ptr_out) {
    n = _n; m = _m;
    
    double x = 0;

    fwrite(&n, sizeof(int), 1, ptr_out);
    fwrite(&m, sizeof(int), 1, ptr_out);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fwrite(&x, sizeof(double), 1, ptr_out);
        }
    }

}
double get_matrix(int n, int m, int i, int j, FILE *ptr_out) {
    fseek(ptr_out, offset(i, j, n, m), SEEK_SET);
    double x = 0;
    fread(&x, sizeof(double), 1, ptr_out); 
    return x;

}
void set_matrix(int n, int m, int i, int j, double x) {
    fseek(ptr_out3, offset(i, j, n, m), SEEK_SET);
    fwrite(&x, sizeof(double), 1, ptr_out3);
}

void sum(int n1, int m1, int n2, int m2) {
    

    if (n1 != n2 || m1 != m2) {
        printf("Impossimatrix to add");
        return ;
    }
    new_matrix(n1, m1, ptr_out3);
    int N = n1, M = m1;

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            double x = get_matrix(n1, m1, i, j, ptr_out1);
            x += get_matrix(n2, m2, i, j, ptr_out2);
            set_matrix(N, M, i, j, x);
        }
    }
}
void prod(int n1, int m1, int n2, int m2) {
    if (n2 != m1) {
        printf("Impossimatrix to multiply");
        return ;
    }
    new_matrix(n1, m2, ptr_out3);
    int N = n1;
    int M = m2;
    //c[i][j] = a[i][k] * b[k][j]
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m2; ++j) {
            double x = 0;
            for (int k = 0; k < m1; ++k) {
                x += get_matrix(n1, m1, i, k, ptr_out1) * get_matrix(n2, m2, k, j, ptr_out2) ;
            }
            set_matrix(N, M, i, j, x);
        }
    }
}

int main(int argc, char *argv[]) {
    
    if (argc < 5) {
        printf("Usage sum/prod file1 file2 file3");
        return 0;
    }
    ptr_out1 = fopen(argv[2], "rb");
    ptr_out2 = fopen(argv[3], "rb");
    ptr_out3 = fopen(argv[4], "wb");
    int n1, m1, n2, m2;

    fread(&n1, sizeof(int), 1, ptr_out1);
    fread(&m1, sizeof(int), 1, ptr_out1);

    fread(&n2, sizeof(int), 1, ptr_out2);
    fread(&m2, sizeof(int), 1, ptr_out2);
    
    if (strcmp(argv[1], "sum") == 0) {
        sum(n1, m1, n2, m2);
    } else if (strcmp(argv[1], "prod") == 0) {
        prod(n1, m1, n2, m2);
    } else {
        printf("Incorrect use of arguments\n");
    }
            
    return 0;
} 

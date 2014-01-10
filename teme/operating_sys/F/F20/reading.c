#include <stdio.h>
#include <stdlib.h>

#define DIM 100


int main(int argc, char *argv[]) {    
    if (argc < 2) {
        printf("give me at least one file\n");
        return 0;
    }

    int n, m;
    
    FILE *ptr_in = fopen(argv[1], "r");

    fread(&n, sizeof(int), 1, ptr_in);
    fread(&m, sizeof(int), 1, ptr_in);
       

    printf("%d %d\n", n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double x; fread(&x, sizeof(double), 1, ptr_in);
            printf("%lf ", x);
        }
        printf("\n");
    }
    return 0;
}


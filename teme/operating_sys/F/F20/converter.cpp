#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("usage: file1 file2\n");
        return 0;
    }

    FILE *ptr_in = fopen(argv[1], "r");
    if (ptr_in == NULL) {
        printf("Could not find file %s\n", argv[1]) ;
        return 0;
    }
    FILE *ptr_out = fopen(argv[2], "wb");
        
    int n, m;
    double **matrix;

    if (fscanf(ptr_in, "%d %d", &n, &m) != 2) {
        printf("Give me more elements in %s\n", argv[1]);
        return 0;
    }
        
    matrix = (double **)malloc(sizeof(double *) * n);
    
    for (int i = 0; i < n; ++i) {
        matrix[i] = (double *) malloc(sizeof(double) * n);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (fscanf(ptr_in, "%lf", &matrix[i][j]) != 1) {
                printf("Not enough matrix elements in %s\n", argv[1]);
            }
        }
    }

    fwrite(&n, sizeof(int), 1, ptr_out);
    fwrite(&m, sizeof(int), 1, ptr_out);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fwrite(&matrix[i][j], sizeof(double), 1, ptr_out);
        }
    }
    printf("Succesfully converted to binary file\n");
    return 0;
}



#include <bits/stdc++.h>

using namespace std;
int main(int argc, char *argv[]) {


  printf("%d\n", argc);

  for (int i = 0; i < argc; ++i) {
    printf("%s\n", argv[i]);
  }
  int num_rows = 3;
  int num_cols = 4;

  int **mat;
  mat = (int**)malloc(sizeof(int*) * num_rows);

  for (int i = 0; i < num_rows; ++i) {
    mat[i] = (int*)malloc(sizeof(int) * num_cols);
  }
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j) {
      mat[i][j] = i + j;
    }
  }
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j) {
      cout << mat[i][j] << " ";
    }
    cout << "\n";
  }
  return 0;
}

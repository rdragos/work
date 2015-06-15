#include <bits/stdc++.h>
#include <stdarg.h>

using namespace std;


int sample_function(int num_args, ...) {
  va_list args;
  va_start (args, num_args); //initialize the list args

  int sum = 0;
  for (int i = 0; i < num_args; ++i) {
    int num = va_arg(args, int); //gets the next integer;
    sum += num;
  }

  va_end(args);
  return sum;
}
int main() {

  printf("%d\n", sample_function(2, 10, -10));
  printf("%d\n", sample_function(5, 1, 2, 3, 4, 5));
  return 0;
}

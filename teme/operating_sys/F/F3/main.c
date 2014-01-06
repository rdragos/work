#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("give me just a number\n");
        return 0;
    }

    long long x = 0;

    char *buffer = argv[1]; 
    int n = strlen(buffer);
    
    for (int i = 0; i < n; ++i) {
        if (buffer[i] < 0 || buffer[i] > '9') {
            break;
        }
        x = x * 10 + buffer[i] - '0';
    }
    
    
    for (long long i = 2; i * i <= x; ++i) {
        if (x % i) {
            continue;
        }

        int pw = 0;
        while(x % i == 0) {
            x /= i; 
            pw += 1;
        }

        printf("%lld ^ %d\n", i, pw);
    }
    if (x > 1) {
        printf("%lld ^ %d\n", x, 1) ;
    }
    return 0;
}
    

#include <cstdio>
#include <cstring>
#include <iostream>

const int SIGMA = 30;
const int MAXN = 1010;
using namespace std;

string A;
int F[SIGMA];

int main() {
/*
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
*/    
    int T;
    
    for(cin >> T; T--; ) {
        cin >> A;
        
        int n = A.size();

        memset(F, 0, sizeof(F));

        for (int i = 0; i < n / 2; ++i) {
            F[A[i] - 'a'] += 1;
        }

        for (int i = (n / 2) + (n & 1); i < n; ++i) {
            F[A[i] - 'a'] -= 1;
        }

        int ok = 0;

        for (int i = 0; i < SIGMA; ++i) {
            ok |= (F[i] != 0);
        }
        
        if (ok) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }

    return 0;
}


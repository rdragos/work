#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
#include <string>
#include <set>
#include <iomanip>
#include <stack>
#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

const int MAXN = 305;

using namespace std;

ll X[MAXN], Y[MAXN];
ll d[MAXN][MAXN], A[MAXN][MAXN];

inline int max(ll a, ll b) {
    if (a > b)
        return a;
    return b;
}

int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/
    
    int N; cin >> N;
    long double ans = 0;
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            A[i][j] = -(1 << 30);
        }
    }

    for (int i = 1; i <= N; ++i) {
        cin >> X[i] >> Y[i];
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (i == j) {
                continue;
            }
            d[i][j] = 1LL * (X[i] + X[j]) * (Y[i] - Y[j]);
        }
    }
   
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (i == j) {
                continue;
            }
            for (int k = 1; k <= N; ++k) {
                if (k == j || k == i) {
                    continue;
                }
                A[i][k] = max(A[i][k], d[i][j] + d[j][k]);
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            ans = max(ans, A[i][j] + A[j][i]);
        }
    }
   
    cout << setprecision(10) << (ans / 2.0000000);

    return 0;
}

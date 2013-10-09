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

#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long


const int MAXN = 2005;
const int mod = 1000000007;

using namespace std;

int N, A[MAXN], C[MAXN];

int read_data() {
    if (!(cin >> N))
        return 0;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }
    return 1;
}
int count_div(long long x) {
    if (x == 1)
        return 1;
    int cnt = 0;
    long long tot = x;
    for (long long i = 2; i * i <= x; ++i) {
        
        if (x % i) {
            continue;
        }
        tot /= i;
        tot *= (i - 1);
        while(x % i == 0)
            x /= i;
    }
    if (x != 1) {
        tot = tot / x * (x - 1);
    }
    return tot;
}    
int solve() {
    
    for (int i = 1; i <= N; ++i) { 
        C[i] = count_div(A[i]);
    }
/* 
    for (int i = 1; i <= N; ++i) {
        cout << A[i] << " " ;
    }
    cout << "\n";
    for (int i = 1; i <= N; ++i) {
        cout << C[i] << " " ;
    }
    cout << "\n";
*/    long long p = 1;

    for (int i = 1; i <= N; ++i) {
        p = 1LL * p * C[i] ;
        p %= mod;
    }

    return p;
}
int main() {
//    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
    while(read_data()) {
        cout << solve() << "\n";
    }
    return 0;
}

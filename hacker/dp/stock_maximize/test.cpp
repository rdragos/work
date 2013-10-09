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
#include <stack>
#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

const int MAXN = 50001;

using namespace std;


int C[MAXN], N;
long long m[MAXN];
inline ll max(ll a, ll b) {
    if (a > b)
        return a;
    return b;
}

inline ll solve() {
    
    m[N - 1] = m[N] = C[N - 1];
    
    for (int i = N - 2; i >= 0; --i) {
        m[i] = max(m[i + 1], C[i]);
    }
/*
    for (int i = 0; i < N; ++i)
       cerr << m[i] << " ";
    cerr << "\n"; 
*/
    ll profit = 0, cnt_profit = 0;
    
    for (int i = 0; i < N; ++i) {
        if (C[i] < m[i]) {
            profit -= C[i];
            cnt_profit += 1;
        }
        else {
            if (C[i] == m[i]) {
                profit += cnt_profit * C[i];
                cnt_profit = 0;
            }
        }

    }
    return profit;
}
int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    int T; cin >> T;

    while(T--) {
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> C[i];

        cout << solve() << "\n";
        
    }

    return 0;
}

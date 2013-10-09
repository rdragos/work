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

using namespace std;

const int MAXN = 105;
int S[MAXN], A[MAXN];
int N;
int ans;
int main() {
/*
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
*/    
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i]; 
        S[i] = S[i - 1] + A[i];
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = i; j <= N; ++j) {
            int b = S[j] - S[i - 1];
            int c = j - i + 1 - b;
            ans = max(ans, c + S[N] - b);
        }
    }
    cout << ans << "\n";
    return 0;
}

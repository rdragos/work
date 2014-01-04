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
#include <unordered_map>

#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

const int MAXN = 102;

using namespace std;

char mark[MAXN][MAXN];

inline bool eliminated(int i, int j) {
    if(i > j) {
        return 1;
    }
    return mark[i][j];
}

int solve(string &s) {
    int n = s.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mark[i][j] = 0;
        }
    }

    for (int i = 1; i < n - 1; ++i) {
        if(s[i - 1] == s[i + 1]) {
            mark[i - 1][i + 1] = 1;
        }
    }
    for (int nr = 3; nr < n; ++nr) {
        for (int i = 0; i + nr < n; ++i) {
            int j = i + nr;

            for (int k = i + 1; k <= j; ++k) {
                if(eliminated(i, k - 1) && eliminated(k, j)) {
                    mark[i][j] = 1;
                }
                if(s[i] == s[j] && eliminated(i + 1, k - 1) && eliminated(k + 1, j - 1)) {
                    mark[i][j] = 1;
                }
            }
        }
    }
    return mark[0][n - 1];
}
int main() {
    ifstream cin("palin3.in");
    ofstream cout("palin3.out");
    

    int T; cin >> T;
    
    for (; T--; ) {
        string s;
        cin >> s;

        int ans = solve(s);
        if(ans == 0) {
            cout << "NU\n";
        } else {
            cout << "DA\n";
        }
    }
    return 0;
}

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

const int MAXN = 10005;
using namespace std;

int prev[MAXN], next[MAXN], CF[MAXN][26], CB[MAXN][26];
int totp[MAXN][30], totn[MAXN][30];
inline int f(char x) {
    return x - 'a';
}

void clear_data() {
    for (int i = 0; i < MAXN ; ++i) {
        next[i] = prev[i] = 0;
        for (int k = 0; k < 26; ++k) {
            CF[i][k] = CB[i][k] = 0;
            totp[i][k] = totn[i][k] = 0;
        }
    }
}
int solve(string &A) {
    
    int n = A.size();
    clear_data();
    int pr = 0;
    int cnt = 0;
    for (int i = 1; i <= n - 2; ++i)
        cnt += (A[i] == '#');
    if (cnt < 3)
        return 0;
    for (int i = 1; i <= n - 2; ++i) {
        for (int k = 0; k < 26; ++k)
            totp[i][k] = totp[i - 1][k];
        if (A[i] == '#') {
            prev[i] = pr;
            pr = i;
            for (int k = 0; k < 26; ++k)
                CF[i][k] = 0;
        }
        else {
            for (int k =0; k < 26; ++k) {
                CF[i][k] = CF[i - 1][k];
            }
            totp[i][f(A[i])] += 1;
            CF[i][f(A[i])] += 1;
        }
    }

    int nx = n - 1;
    
    for (int i = n - 2; i >= 1; --i) {
        
        for (int k = 0; k < 26; ++k)
            totn[i][k] = totn[i + 1][k];

        if (A[i] == '#') {
            next[i] = nx;
            nx = i;
            for (int k = 0; k < 26; ++k)
                CB[i][k] = 0;
        }
        else {
            
            for (int k = 0; k < 26; ++k) {
                CB[i][k] = CB[i + 1][k];
//                totn[i][k] = totn[i + 1][k];
            }
            totn[i][f(A[i])] += 1;
            CB[i][f(A[i])] += 1;
        }
    }
    int ans = 0;

    for (int i = 1; i <= n - 2; ++i) {
        if (A[i] != '#')
            continue;
        if (prev[i] == 0 || next[i] == n - 1)
            continue;
        int c1, c2, c3, c4;
        c1 = c2 = c3 = c4 = 0;
//          there is a piece like this string1#string2#string3#string4
        
        // string1
        for (int k = 0 ; k < 26; ++k)
            c1 = max(c1, totp[prev[i] -1][k]);
            //string4

        for (int k = 0; k < 26; ++k)
            c2 = max(c2, totn[next[i] + 1][k]);
        //string2
        for (int k = 0; k < 26; ++k)
            c3 = max(c3, CF[i - 1][k]);
        //string3
        for (int k = 0; k < 26; ++k)
            c4 = max(c4, CB[i + 1][k]);
 
        if (c1 == 0 || c2 == 0 || c3 == 0 || c4 == 0)
            continue;
//            cerr << prev[i] << " " << i << " " << next[i] << "\n";
//            cerr << c1 << " " << c2 << " " << c3 << " " << c4 << "\n";
        ans = max(ans, c1 + c2 + c3 + c4 + 3);
    }
    return ans;
}    
int main() {

//   freopen("test.in", "r", stdin);
//   freopen("test.out", "w", stdout);
    
    int T;
    string S; 
    for (cin >> T; T-- ; ) {
        S = "#";
        string A;
        cin >> A;
        S += A;
        S += "#";
        cout << solve(S) << "\n";
    }
   
    return 0;
}

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

const int MAXN = 105;

using namespace std;

int d[MAXN][MAXN][MAXN];
int t[MAXN][MAXN][MAXN];
string A, B, C;

inline int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
void reconst(int k, int i, int j) {
    if(i == 0 || j == 0) {
        return ;
    }
    if (A[i] == B[j]) {
        if (k > 0) {
            if (A[i] == C[k]) {
                reconst(k - 1, i - 1, j - 1);
            }
            else {
                reconst(k, i - 1, j - 1);
            }

        }
        else {
            reconst(k, i - 1, j - 1);
        }
    }
    else if (d[k][i - 1][j] == d[k][i][j]) {
        reconst(k, i - 1, j);
    }
    else if(d[k][i][j - 1] == d[k][i][j]) {
        reconst(k, i, j - 1);
    }
    if (A[i] == B[j]) {
        cout << A[i];
    }
}
int main() {

    ifstream cin("test.in");
    ofstream cout("test.out");
    
    string S;

    A = "."; B = ".", C = ".";
    
    cin >> S; A += S;
    cin >> S; B += S; 
    cin >> S; C += S;
    for (int k = 1; k < C.size(); ++k) {
        for (int i = 1; i < A.size(); ++i) {
            for (int j = 1; j < B.size(); ++j) {
                if (A[i] != B[j]) 
                    d[k][i][j] = max(d[k][i][j], max(d[k][i - 1][j], d[k][i][j - 1]));
                if (A[i] == B[j]) {
                    if (A[i] == C[k]) {
                        d[k][i][j] = max(d[k][i][j], d[k - 1][i - 1][j - 1] + 1);
                    }
                    if (A[i] != C[k]) {
                        d[k][i][j] = max(d[k][i][j], d[k][i - 1][j - 1] + 1);
                    }
                }
            }
        }
    }
    
    int ans = 0, pos = 1;

    for (int k = 0; k < C.size() - 1; ++k) {
        cerr << d[k][A.size() - 1][B.size() - 1] << " ";
        if (ans < d[k][A.size() - 1][B.size() - 1]) {
            ans = d[k][A.size() - 1][B.size() - 1];
            pos = k;
        }
    }
    if (ans == 0) {
        cout << 0 << "\n";
        return 0;
    }
    reconst(pos, A.size() - 1, B.size() - 1);
    
    return 0;
}

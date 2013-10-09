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


const int MAXN = 305;

using namespace std;


int D[MAXN][MAXN];
int N;

int check() {
    
    for (int k = 1; k <= N; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (i == j || i == k || k == j) {
                    continue;
                }
                if (D[i][j] > D[i][k] + D[k][j]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
int main() {
/* 
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    cin >> N;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            cin >> D[i][j];
    }
    
    if (check() == 0) {
        cout << -1; 
        return 0;
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            cout << D[i][j] << " " ;
        cout << "\n";
    }

    return 0;
}

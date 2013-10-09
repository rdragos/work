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

const int MAXN = 2005;
const int off = 2;

using namespace std;

int N, C;
int S1[MAXN][MAXN], S2[MAXN][MAXN], D[MAXN][MAXN];
int mat[MAXN][MAXN];

int main() {
    ifstream fin("test.in");
    ofstream fout("test.out");
    
    fin >> N;

	for (int i = 1; i <= N; i++) {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        x1 += off; y1 += off; x2 += off; y2 += off;

        mat[x1][y1] += 1;
        mat[x1][y2 + 1] -= 1;
        mat[x2 + 1][y2 + 1] += 1;
        mat[x2 + 1][y1] -= 1;
    }
 
    int cnt = 0;
    C = 10;
    for (int i = off-1; i <= C; i++) {
        for (int j = off-1; j <= C; j++) {
            
            S1[i][j] = S1[i][j - 1] + mat[i][j];
            S2[i][j] = S2[i - 1][j] + mat[i][j];
            D[i][j] = S1[i][j - 1] + S2[i - 1][j] + D[i - 1][j - 1] + mat[i][j];
            printf ("%d ", D[i][j]);
            cnt += (D[i][j] == N);
        }
        printf("\n");
    }
    fout << cnt << "\n";
    return 0;
}

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

const int MAXN = 20;

using namespace std;

char A[MAXN][MAXN];
int N, M;
set <pair <int, int> > cnt[MAXN][MAXN];
set <pair <int, int> > dp[MAXN][MAXN];

void clear_data() {
    memset(A, '\0', sizeof(A));
    
}
void add(int i, int j, set <pair <int, int> > &s) {
    for (set <pair <int, int> > :: iterator it = s.begin(); it != s.end(); ++it)
        dp[i][j].insert(*it);
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    
    int T;

    for (scanf("%d\n", &T); T--; ) {
        clear_data();
        scanf("%d %d\n", &N, &M);
        for (int i = 1; i <= N; ++i) {
            gets(A[i] + 1);
        }

        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= M; ++j)
                for (int k = -1; k <= 1; ++k)
                    for (int l = -1; l <= 1; ++l)
                        if(A[i + k][j + l] == '1')
                            cnt[i][j].insert( make_pair(i + k, j + l) );
    
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j)
                printf("%d", cnt[i][j].size());
            printf("\n");
        }
    
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                       
                int ai = 0, aj = 0;
                add(i, j, cnt[i][j]);
                for (set <pair <int, int > > :: iterator it = cnt[i][j].begin(); it != cnt[i][j].end(); ++it) {
                    ai += (dp[i - 1][j].find(*it) == dp[i - 1][j].end());
                    aj += (dp[i][j - 1].find(*it) == dp[i][j - 1].end());
                }
//                cerr << ai << " " << aj << "\n"; 
                if (aj + dp[i][j - 1].size() < ai + dp[i - 1][j].size()) {
                    add(i, j, dp[i][j - 1]);
                } else {
                    add(i, j, dp[i - 1][j]);
                }
            }
        }
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) 
                printf("%d ", dp[i][j].size());
            printf("\n");
        }
        printf("%d\n", dp[N][M].size());
        
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= M; ++j)
                cnt[i][j].clear(), dp[i][j].clear();
    }

    return 0;
}

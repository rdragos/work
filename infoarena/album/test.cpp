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

const int MAXN = 1002;
const int MAXK = 52;
using namespace std;

int save[MAXK];

int**M;
int N, K;
int best[MAXK];

void afiseaza() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M[i][0]; ++j) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

inline bool cmp(const int*a, const int*b) {
    for (int i = 1; i <= min(a[0], b[0]); ++i) {
        if (a[i] < b[i]) {
            return 1;
        }
        if (a[i] > b[i]) {
            return 0;
        }
    }
    return a[0] < b[0];
}
inline int score(int L, int prev) {
    
    int cnt = 1;
    for (int j = 1; j <= M[L][0]; ++j) {
        if (M[L][j] <= M[prev][cnt])
            continue;
        cnt += 1;
    }
    return cnt;
}
int main() {

    freopen("debug.out", "w", stdout);
    ifstream fin("album.in");
    ofstream fout("album.out");
    
    fin >> N >> K;
    M = new int*[N+1];
    for (int i = 1; i <= N; ++i) {
        M[i] = new int[K+2];
        for (int j = 1; j <= K; ++j) {
            fin >> M[i][j];
        }
        sort(M[i] + 1, M[i] + K + 1);
        M[i][0] = K;
    }
    sort(M + 1, M + N + 1, cmp);
    int remaining, begin_line;
    remaining = N * K;
    begin_line = 1;
    
    for (int go = 1; go <= N; ++go) {
        
        afiseaza();
        int p = 1;
        
        for (int i = begin_line + 1; i <= N; ++i) {
            if (i < N) {
                cerr << score(i,i-p) << " " << score(i+1,i-p) ;
                if (score(i,i-p) < score(i+1,i-p)) {
                   p += 1;  
                   continue;
                }
                else {
                    p = 1;
                }
            }else {
                p = 1;
            }
            for (int j = 1; j <= M[i][0]; ++j) {
                if (M[i][j] <= M[i - p][1])
                    continue;
                
                save[0] = 0;
                for (int k = j; k <= M[i][0]; ++k)
                    save[++save[0]] = M[i][k];
                for (int k = 1; k < j; ++k)
                    save[++save[0]] = M[i][k];
                for (int k = 1; k <= M[i][0]; ++k)
                    M[i][k] = save[k];
                break;
            }
        }

        printf("after permutation\n");
        afiseaza();

        for (int i = N; i >= begin_line + 1; --i) {
            save[0] = 0;
            for (int j = 1; j <= M[i][0]; ++j) {
                if (M[i][j] > M[i - 1][j]) {
                    remaining -= 1;
                    continue;
                }
                save[++save[0]] = M[i][j];
            }
            
            M[i][0] = save[0];

            for (int j = 1; j <= save[0]; ++j)
                M[i][j] = save[j];
        }
        remaining -= M[begin_line][0];
        M[begin_line][0] = 0; 
        if (remaining == 0) {
            fout << go << "\n";
            return 0;
        }

        for (int i = begin_line + 1; i <= N; ++i) {
            sort(M[i] + 1, M[i] + M[i][0] + 1);
        }
        sort(M + begin_line + 1, M + N + 1, cmp);
        
        for (int i = 1; i <= N; ++i)
            if (M[i][0] > 0) {
                begin_line = i;
                break;
            }
//        afiseaza();

    }

                
    return 0;
}

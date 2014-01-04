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

const int MAXN = 15005;

using namespace std;


vector <int> G[MAXN];
int v[MAXN];
int viz[MAXN];
long long D[MAXN];

void DF(int node) {
    viz[node] = 1;

    for (auto &it : G[node]) {
        if (!viz[it]) {
            DF(it);
        }
    }
    for (auto &it: G[node]) {
        D[node] = max(D[node], D[it]);
    }
    D[node] += v[node];

}

int main() {
    ifstream cin("easygraph.in");
    ofstream cout("easygraph.out");
    
    int T; cin >> T;
    while(T--) {
        int N, M; cin >> N >> M;
        
        for (int i = 0; i < N; ++i) {
            cin >> v[i];
            //clearing
            G[i].clear();
            D[i] = 0;
            viz[i] = 0;
        }

        for (int i = 0; i < M; ++i) {
            int x, y;
            cin >> x >> y; x--; y--;
            G[x].push_back(y);
        }
        for (int i = 0; i < N; ++i) {
            if (!viz[i]) {
                DF(i);
            }
        }
        long long answer = -1LL << 40;
        for (int i = 0; i < N; ++i) {
            answer = max(answer, D[i]);
        }
        cout << answer << "\n";
    }   
    return 0;
}

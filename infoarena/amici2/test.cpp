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

using namespace std;


int BF(const vector <vector <int> > &G, const int &N) {
    queue <int> Q;
    Q.push(0);
    vector <int> distance(G.size());
    distance[0] = 1;
    
    while(!Q.empty()) {
        int x = Q.front();
        Q.pop();

        for (auto& it: G[x]) {
            if (distance[it]) {
                continue;
            }
            distance[it] = distance[x] + 1;
            Q.push(it);
        }
    }
    
    int mx = 0;
    for (int i = 0; i < N; ++i) {
        if (distance[i] == 0) {
            return 0;
        }
        mx = max(mx, distance[i] - 1);
    }
    int step;
    for (step = 0; (1 << step) <= mx; ++step); 
    return step;
}
int main() {
    ifstream cin("amici2.in");
    ofstream cout("amici2.out");
    
    int T; cin >> T;
    while(T--) {
        int N, M;
        cin >> N >> M;
        vector <vector <int> > G(N);
        for(; M--; ) {
            int x, y; cin >> x >> y; 
            x -= 1; y -= 1;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        cout << BF(G, N) << "\n";
    }
    return 0;
}

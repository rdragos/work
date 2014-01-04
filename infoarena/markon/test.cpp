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

int main() {
    ifstream cin("markon.in");
    ofstream cout("markon.out");
    
    int N, M, X; cin >> N >> M >> X; --X;
    vector <int> v(N);
    vector <vector <int> > edges(N, vector <int>());
    vector <bool> inQ(N, false), visited(N, false);
    vector <int> unmark(N, 0);

    for (int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    
    for (int i = 0; i < M; ++i) {
        int x, y; cin >> x >> y;
        x--; y--;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    
    for (int i = 0; i < N; ++i) {
        unmark[i] = edges[i].size();
    }

    queue <int> Q;
    Q.push(X); visited[X] = true;

    vector <int> answer;

    while(!Q.empty()) {
        int node = Q.front(); Q.pop();
        answer.push_back(node);
        for (size_t i = 0; i < edges[node].size(); ++i) {
            --unmark[edges[node][i]];
        }
        if (v[node] > unmark[node] || v[node] == 0) {
            for (size_t i = 0; i < edges[node].size(); ++i) {
                if (!visited[edges[node][i]]) {
                    Q.push(edges[node][i]);
                    visited[edges[node][i]] = 1;
                }
            }
        } else {
            inQ[node] = true;
        }

        for (size_t i = 0; i < edges[node].size(); ++i) {
            int x = edges[node][i];
            if (!inQ[x] || v[x] <= unmark[x]) {
               continue;
            }
            inQ[x] = false;
            for (size_t j = 0; j < edges[x].size(); ++j) {
                int y = edges[x][j];
                if (!visited[y]) {
                    visited[y] = 1;
                    Q.push(y);
                }
            }
        }
    }
    cout << answer.size() << "\n";
    for (size_t i = 0; i < answer.size(); ++i) {
        cout << answer[i] + 1 << "\n";
    }
    return 0;
}

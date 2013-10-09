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


const int MAXN = 205;

using namespace std;

vector <pair <int, int> > G[MAXN];
int d[MAXN];
int D[MAXN][MAXN];
int N, M, x[MAXN], y[MAXN], w[MAXN];
int s[MAXN];

struct cmp {
    bool operator()(const int &a, const int &b) {
        return d[a] > d[b];
    }
};

void dijkstra(int node) {
    priority_queue <int, vector <int>, cmp> pq;
    
    char visited[MAXN];
    memset(visited, 0, sizeof(visited));
    memset(d, 1 << 30, sizeof(d));

    d[node] = 0;
    pq.push(node);

    while(!pq.empty()) {

        int c_n = pq.top();
        pq.pop();
        visited[c_n] = 0;
        for (vector <pair <int, int> > :: iterator it = G[c_n].begin(); it != G[c_n].end(); ++it) {
            if (d[it -> first] > d[c_n] + it -> second) {
                d[it -> first] = d[c_n] + it -> second;
                if (!visited[it -> first]) {
                    pq.push(it -> first);
                    visited[it -> first] = 1;
                }
            }
        }
    }

    for (int i = 1; i <= N; ++i)
        D[node][i] = d[i];

}
int main() {
    ifstream cin("test.in");
    ofstream cout("test.out");
    

    cin >> N >> M;

    for (int i = 1; i <= M; ++i) {
        cin >> x[i] >> y[i] >> w[i];
        G[x[i]].push_back(make_pair(y[i], w[i]));
    }

    for (int i = 1; i <= N; ++i) 
        dijkstra(i);
    
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            s[i] += D[i][j];
    
    for (int i = 1; i <= M; ++i) {
        
    return 0;
}

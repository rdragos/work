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

const int INF = 1e9 + 1;
class Graph {
  vector< map <int, ll> > edges;
  int N;

 public:
  Graph(int _N) {
    N = _N;
    edges.assign(N, map<int,ll>());
  }

  void addEdge(int x, int y, int cap) {
    x--; y--;
    edges[x][y] += cap;
    edges[y][x] += cap;
  }

  ll solve() {

    queue <int> Q;
    vector<int> vis(N,0);

    for (int i = 1; i < N - 1; ++i) {
      if (edges[i].size() == 2) {
        Q.push(i);
        vis[i] = 1;
      }
    }
    while(!Q.empty()) {
      int to_del = Q.front();
      Q.pop();

      if (to_del == 0 || to_del == N - 1) {
        continue;
      }

//      cerr << "erasing: " << to_del + 1<< "\n";
      vector<pair<int, ll> > v;
      for (auto n: edges[to_del]) {
        v.push_back(make_pair(n.first, n.second));
      }
      edges[to_del].clear();

      int x = v[0].first;
      int y = v[1].first;
      int m = min(v[0].second, v[1].second);
      edges[x].erase(edges[x].find(to_del));
      edges[y].erase(edges[y].find(to_del));

      edges[x][y] += m;
      edges[y][x] += m;
      if (edges[x].size() == 2 && !vis[x]) {
        Q.push(x);
        vis[x] = 1;
      }
      if (edges[y].size() == 2 && !vis[y]) {
        Q.push(y);
        vis[y] = 1;
      }

//      cerr << "placing " << x + 1 << " to " << y + 1 << " with " << edges[x][y] << "\n";
    }
    return edges[0][N - 1];
  }
};
int main() {
  ifstream cin("symmetricgraph2.in");
  ofstream cout("symmetricgraph2.out");

  int N, M; cin >> N >> M;
  Graph G(N);

  for (int i = 0; i < M; ++i) {
    int x, y, z; cin >> x >> y >> z;
    G.addEdge(x, y, z);
  }

  cout << G.solve();
  return 0;
}

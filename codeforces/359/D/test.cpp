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

class Graph {
public:
  Graph(int _N) {
    N = _N;
    edges.assign(N + 1, vector<int>());
    vis.assign(N + 1, 0);
    subsize.assign(N + 1, 1);
    centroid.assign(N + 1, 0);
    parent.assign(N + 1, 0);
    parent[1] = 0;
  }

  void addEdge(int x, int y) {
    edges[x].push_back(y);
  }

  void dfs(int node) {
    for (auto neigh: edges[node]) {
      dfs(neigh);
      parent[neigh] = node;
      subsize[node] += subsize[neigh];
    }

    int cand = node;
    centroid[node] = node;
    for (auto neigh: edges[node]) {
      if (subsize[neigh] * 2 > subsize[node]) {
        cand = neigh;
      }
    }
    centroid[node] = centroid[cand];

    for (; ; ) {
      int left = subsize[centroid[node]];
      int right = subsize[node] - left;
      if (2 * right > subsize[node]) {
        centroid[node] = parent[centroid[node]];
      } else {
        break;
      }
    }
  }
  void solve() {
    dfs(1);
  }

  int find_centroid(int node) {
    return centroid[node];
  }


private:
  vector<int> centroid, subsize, vis, parent;
  vector<vector<int>> edges;
  int N;

};
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N, Q; cin >> N >> Q;
  Graph G(N);

  for (int i = 2; i <= N; ++i) {
    int p; cin >> p;
    G.addEdge(p, i);
  }
  G.solve();
  while(Q--) {
    int n; cin >> n;
    cout << G.find_centroid(n) << "\n";
  }
  return 0;
}

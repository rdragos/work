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
     vis.assign(N + 1, -1);
   }

   void addEdge(int x, int y) {
     edges[x].push_back(y);
     edges[y].push_back(x);

     allEdges.push_back(make_pair(x, y));
   }

   void dfs(int node, int col) {
     vis[node] = col;
     for (auto v: edges[node]) {
       if (vis[v] == -1) {
         dfs(v, col ^ 1);
       }
     }
   }
   vector<vector<int>> solve() {
     vector<vector<int>> cover(2, vector<int>());

     for (int i = 1; i <= N; ++i) {
       if (vis[i] == -1) {
         dfs(i, 1);
       }
     }
     /*
     for (int i = 1; i <= N; ++i) {
       cerr << i << " " << vis[i] << "\n";
     }
     */
     for (auto e: allEdges) {
       if (vis[e.first] == vis[e.second]) {
         return vector<vector<int>>{};
       }
     }
     for (int i = 1; i <= N; ++i) {
       cover[vis[i]].push_back(i);
     }

     sort(cover[0].begin(), cover[0].end());
     sort(cover[1].begin(), cover[1].end());
     return cover;
   }

   vector<pair<int, int>> allEdges;
   vector<vector <int>> edges;
   vector<int> vis;
   int N;

};
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N, M; cin >> N >> M;


  Graph G(N);
  for (int i = 0; i < M; ++i) {
    int x, y; cin >> x >> y;
    G.addEdge(x, y);
  }

  vector<vector<int>> answer = G.solve();
  if (answer.size() == 0) {
    cout << -1;
  } else {
    cout << answer[0].size() << "\n";
    for (auto v: answer[0]) {
      cout << v << " " ;
    }
    cout << "\n";
    cout << answer[1].size() << "\n";
    for (auto v: answer[1]) {
      cout << v << " ";
    }
  }
  return 0;
}

#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <iomanip>
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
     sums.assign(N + 1, 0);
     dist.assign(N + 1, 0);
   }
   void addEdge(int x, int y) {
     edges[x].push_back(y);
   }

   void dfs(int node) {
     sums[node] = 1;
     for (auto n: edges[node]) {
       dfs(n);
       sums[node] += sums[n];
     }
   }
   void dfs2(int node) {
     int other_sum = 0;

     for (auto n: edges[node]) {
       dist[n] = dist[node] + 1.0;
       other_sum += sums[n];
     }
     for (auto n: edges[node]) {
       dist[n] += (other_sum - sums[n]) / 2.0;
       dfs2(n);
     }
   }
   vector<long double> solve() {
     dfs(1);
     dist[1] = 1.0;
     dfs2(1);

     return dist;
   }
   int N;
   vector<vector<int>> edges;
   vector<int> sums;
   vector<long double> dist;
};
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N; cin >> N;
  Graph G(N);
  for (int i = 2; i <= N; ++i) {
    int x; cin >> x;
    G.addEdge(x, i);
  }

  cout << setprecision(10);

  vector<long double> ans = G.solve();
  for (int i = 1; i <= N; ++i) {
    cout << ans[i] << " " ;
  }

  return 0;
}

#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
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

const int INF = 1 << 29;

class Graph {
 public:
   Graph(int _N) {
     N = _N;
     edges.assign(N + 1,vector<int>());
     dist.assign(N + 1, vector<int>(N + 1, INF));
     for (int i = 1; i <= N; ++i) {
       dist[i][i] = 0;
     }
   }

   void addEdge(int x, int y) {
     edges[x].push_back(y);
     edges[y].push_back(x);

     dist[x][y] = dist[y][x] = 1;
   }

   void compute_distances() {
     for (int k = 1; k <= N; ++k) {
       for (int i = 1; i <= N; ++i) {
         for (int j = 1; j <= N; ++j) {
           dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
         }
       }
     }
   }


   double compute_day2(int from, int d) {

     vector <int> candidates;
     vector <double> prob(N + 1, 0);
     vector <double> max_prob(N + 1, 0);
     vector <bool> vis(N + 1, false);

     for (int i = 1; i <= N; ++i) {
       if (dist[from][i] == d) {
         for (auto neigh: edges[i]) {
           if (!vis[neigh]) {
             candidates.push_back(neigh);
             vis[neigh] = true;
           }
           prob[neigh] += 1.0 / N / edges[i].size();
         }
       }
     }
     //fix the second

     double max_sum = 0;
     for (int j = 1; j <= N; ++j) {

       double sum_prob = 0;
       for (auto neigh: candidates) {
         int d = dist[j][neigh];
         max_prob[d] = max(max_prob[d], prob[neigh]);
       }
       for (auto neigh: candidates) {
         int d = dist[j][neigh];
         sum_prob += max_prob[d];
         max_prob[d] = 0;
       }
       max_sum = max(max_sum, sum_prob);
     }
     return max_sum;
   }
   double solve() {
     compute_distances();
     double answer = 0;
     for (int i = 1; i <= N; ++i) {
       //fix first vertex
       double cur_prob = 0;
       for (int d1 = 0; d1 <= N; ++d1) {
         //fix the distance
         int cnt = 0;
         for (int j = 1; j <= N; ++j) {
           if (dist[i][j] == d1) {
             cnt += 1;
           }
         }
        if (cnt == 0) {
          continue;
        }
        //bullseye from the first time
        double prob = 1 / (1.0 * N);
        cur_prob += max(prob, compute_day2(i, d1));
       }
       answer = max(answer, cur_prob);
     }
     return answer;
   }
 private:
   int N;
   vector<vector<int>> edges;
   vector< vector <int>> dist;
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

  cout << setprecision(10);
  cout << G.solve();
  return 0;
}

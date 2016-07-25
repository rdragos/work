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
     parents.assign(N + 1, vector<int>());
     init_par.assign(N + 1, 0);
     instack.assign(N + 1, false);
   }
   void addParent(int child, int parent) {
     edges[parent].push_back(child);
     init_par[child] = parent;
   }

   void dfs(int node) {
     vis[node] = 1;
     instack[node] = true;
     cur_stack.push_back(node);

     for (auto neigh: edges[node]) {
       if (instack[neigh]) {
         if (node == neigh) {
           duplicates.push_back(node);
         } else {
           //cerr << "on cycle: " << neigh << "\n";
           cycles.push_back(neigh);
         }
       } else {
         dfs(neigh);
       }
     }
     instack[node] = false;
     cur_stack.pop_back();
   }
   pair<int, vector<int>> solve() {
     for (int i = 1; i <= N; ++i) {
       if (!vis[i]) {
         dfs(i);
       }
     }

     int root = 1;
     if (duplicates.size() > 0) {
       root = duplicates[0];
     } else if (cycles.size() > 0) {
       root = cycles[0];
     }
     vector<int> answer(init_par);
     int changes = 0;
     for (auto single: cycles) {
       changes += 1;
       answer[single] = root;
     }
     for (int i = 1; i < duplicates.size(); ++i) {
       changes += 1;
       answer[duplicates[i]] = root;
     }
     return make_pair(changes, answer);
   }

   int N;
   vector<int> vis;
   vector <vector <int>> edges, parents;
   vector<int> cycles;
   vector<int> duplicates;
   vector<int> cur_stack;
   vector<bool> instack;
   vector<int> init_par;
};
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N; cin >> N;
  Graph G(N);
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    G.addParent(i, x);
  }
  pair<int, vector<int>> answer = G.solve();
  cout << answer.first << "\n";
  for (int i = 1; i <= N; ++i) {
    cout << answer.second[i] << " " ;
  }
  return 0;
}

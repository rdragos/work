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
#include <omp.h>
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
        viz.assign(N, 0);
        L.assign(N, -1);
        R.assign(N, -1);
        edges.assign(N, vector<int>());
        edge_mask.assign(N, 0);
    }
    void addEdge(int x, int y) {
        edges[x].push_back(y);
        edge_mask[y] |= (1 << x);
    }

    bool pairup(int node) {
        if (viz[node]) {
             return 0;
        }
        viz[node] = 1;
        for (auto vec: edges[node]) {
            if (R[vec] == -1) {
                L[node] = vec;
                R[vec] = node;
                return 1;
            }
        }
        for (auto vec: edges[node]) {
            if (pairup(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return 1;
            }
        }
        return 0;
    }
    bool maxMatch() {
        int change = 1;
        while(change) {
            change = 0;
            for (int i = 0; i < N; ++i) {
                viz[i] = 0;
            }
            for (int i = 0; i < N; ++i) {
                if (L[i] == -1) {
                    change |= pairup(i);
                }
            }
        }
        for (int i = 0; i < N; ++i) {
            if (L[i] == -1) {
                return 0;
            }
        }
        return 1;
    }
    void write() {
        for (int i = 0; i < N; ++i) {
            vector<int> row;
            for (int j = 0; j < N; ++j) {
                if ( edge_mask[i] & (1 << j) ) {
                    row.push_back(j);
                }
            }
            if (R[i] != -1) {
                cerr << R[i] << " -> ";
            } else {
                cerr << "?" <<  " -> ";
            }
            cerr << "{";
            for (int j = 0; j < row.size() - 1; ++j) {
                cerr << row[j] << ",";
            }
            cerr << *row.rbegin() << "}\n";
        }
    }
    int N;
    vector<int> viz, L, R, edge_mask;
    vector<vector<int>> edges;
};

class Solver {

    vector <int> current_set;
    int N, count_set;
    set<vector<int>> unique_sets;

 public:
     Solver(int _N) {
         N = _N;
         count_set = 0;
     }

     bool intersect(int mask1, int mask2) {
         return (mask1 & mask2);
     }

     bool do_matching(const vector<int>& to_check) {
         //debug_set(to_check);
         //
         int ret = prime_condition(to_check);
         if (ret == 0) {
             return 0;
         }
         Graph G(N);
         // prob cache misses?
         for (int i = 0; i < N; ++i) {
             for (int j = 0; j < N; ++j) {
                 if (to_check[j] & (1 << i)) {
                     G.addEdge(i, j);
                 }
             }
         }
         for (int i = 0; i < N; ++i) {
             if (G.edges[i].size() == 0) {
                 return 0;
             }
         }

         if (!G.maxMatch()) {
                 cout << "FAIL ON\n";
                 cout << "is prime condition? " << ret << "\n";
                 G.write();
                 return 0;
         }
         //cout << "set: " << count_set << "\n";
         //cerr << "MATCHING DONE?\n";
         /*
         vector<int> tmp(to_check);
         sort(tmp.begin(), tmp.end());
         unique_sets.insert(tmp);
         */
         return 1;
     }

     void generate_all_sets(int k, vector<int>& current_set) {
         if (k == N) {
             count += do_matching(current_set);
         } else {
             int start = 0;
             if (k != 0) {
                 start = current_set[k - 1];
             }
             #pragma omp parallel for
             for (int mask = start + 1; mask < (1 << N); ++mask) {
                 bool flag = false;
                 for (int i = 0; i < k; ++i) {
                     if (!intersect(mask, current_set[i])) {
                         flag = true;
                         break;
                     }
                 }
                 if (!flag) {
                     vector<int> next_set(current_set);
                     next_set.push_back(mask);
                     generate_all_sets(k + 1, next_set);
                 }
             }
         }
     }

     bool prime_condition(const vector<int>&to_check) {
         for (int i = 0; i < N; ++i) {
             for (int j = 0; j < N; ++j) {
                 if (i == j) {
                     continue;
                 }
                 bool can_go = false;
                 for (int k = 0; k < N; ++k) {
                     if (intersect(to_check[k], 1<<i) && !intersect(to_check[k], 1<<j)) {
                         can_go = true;
//                         cerr << "fails with " << i << " " << j << "\n";
                         break;
                     }
                 }
                 if (!can_go) {
//                     cerr << "pair: " << i + 1 << " " << j + 1 << "\n";
                     return 0;
                 }
             }
         }
         return 1;
     }
    void debug_(vector<int>& edges) {
        for (int i = 0; i < edges.size(); ++i) {
            for (int j = 0; j < N; ++j) {
                if (edges[i] & (1 << j)) {
                    cout << j + 1 << " " ;
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
     void checker() {
         vector<int> empty_vector;
         generate_all_sets(0, empty_vector);
         cout << "Found " << count_set << " matchings\n";
         cout << "Found " << unique_sets.size() << " unique sets\n";
         /*
         for (auto edges: unique_sets) {
             debug_(edges);
         }
         */
     }
};
int main() {
  ifstream cin("test.in");

  int N; cin >> N;
  Solver G(N);
  G.checker();
//  int res = G.do_matching({35,77,161,53,19,13,102,122});
 // cout << res << "\n";
  return 0;
}

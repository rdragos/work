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



class Solver {

    vector <int> current_set;
    int N, count_set;

    vector<vector<int>> edges;
    vector<int> L;
    map <int, int> R;
    vector<int> viz;
    set<vector<int>> unique_sets;

 public:
     Solver(int _N) {
         //
         N = _N;
         count_set = 0;
         edges.assign(N, vector<int>());
         L.assign(N,0);
         viz.assign(N, 0);
     }

     bool intersect(int mask1, int mask2) {
         return (mask1 & mask2);
     }

     void to_set(int mask) {
         cout << "{";
         vector<int> Ans;
         for (int i = 0; i < N; ++i) {
             if (mask & (1 << i)) {
                 Ans.push_back(i + 1);
             }
         }
         for (int i = 0; i < Ans.size() - 1; ++i) {
             cout << Ans[i] << ",";
         }
         if (Ans.size() > 0) {
             cout << Ans[Ans.size() - 1];
         }
         cout << "}";
     }


     bool pairup(int node) {
         if (viz[node]) {
             return 0;
         }
         viz[node] = 1;
         for (auto vec: edges[node]) {
             if (R.find(vec) == R.end()) {
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

     void debug_set(const vector<int>& v) {
         cout << "**********\n";
         for (int i = 0; i < v.size(); ++i) {
             to_set(v[i]);
             cout << "\n";
         }
     }
     bool do_matching(const vector<int>&to_check) {
         //debug_set(to_check);
         //
         int ret = prime_condition(to_check);
         if (ret == 0) {
             return 0;
         }
         for (int i = 0; i < N; ++i) {
            edges[i].clear();
            viz[i] = 0;
            L[i] = -1;
            R.clear();
         }
         for (int i = 0; i < N; ++i) {
             for (int j = 0; j < N; ++j) {
                 if (to_check[j] & (1 << i)) {
                     edges[i].push_back(j);
                 }
             }
         }
         for (int i = 0; i < N; ++i) {
             if (edges[i].size() == 0) {
                 return 0;
             }
         }
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
                 cout << "FAIL ON\n";
                 cout << "is prime condition? " << ret << "\n";
                 write_set(L, to_check);

                 cout << "graph: \n";
                 for (int k = 0; k < N; ++k) {
                     cerr << k + 1 << " -> " ;
                     for (auto vec: edges[k]) {
                         to_set(to_check[vec]);
                     }
                     cerr << "\n";
                 }
                 return 0;
             }
         }
         /*
         cout << "set: " << count_set << "\n";
         write_set(L, to_check);
         */
         //cerr << "MATCHING DONE?\n";
         /*
         vector<int> tmp(to_check);
         sort(tmp.begin(), tmp.end());
         unique_sets.insert(tmp);
         */
         return 1;
     }

     void generate_all_sets(int k) {
         if (k == N) {
             count_set += do_matching(current_set);
         } else {
             for (int mask = 0; mask < (1 << N); ++mask) {
                 bool flag = false;
                 for (int i = 0; i < k; ++i) {
                     if (!intersect(mask, current_set[i]) || current_set[i] == mask) {
                         flag = true;
                     }
                 }
                 if (flag) {
                     continue;
                 }
                 current_set.push_back(mask);
                 generate_all_sets(k + 1);
                 current_set.pop_back();
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
                     }
                 }
                 if (!can_go) {
                     //cerr << "pair: " << i + 1 << " " << j + 1 << "\n";
                     return 0;
                 }
             }
         }
         return 1;
     }

     void write_set(vector<int>& L, const vector<int>&v) {
         for (int i = 0; i < N; ++i) {
             if (L[i] == -1) {
                 cout << "?";
             } else {
                 cout << i + 1;
             }
             cout << " -> ";
             if (L[i] != -1) {
                 to_set(v[L[i]]);
             }
             cout << "\n";
        }
     }
     void checker() {
         generate_all_sets(0);
         cout << "Found " << count_set << " matchings\n";
         cout << "Found " << unique_sets.size() << " unique sets\n";
     }
};
int main() {
  ifstream cin("test.in");

  int N; cin >> N;
  Solver G(N);
  G.checker();
  //cout << G.prime_condition({7,6,5});
  return 0;
}

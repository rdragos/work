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

     bool do_matching(const vector<int>&to_check) {
         for (int i = 0; i < N; ++i) {
            edges[i].clear();
            viz[i] = 0;
            L[i] = -1;
            R.clear();
         }
         for (int i = 0; i < N; ++i) {
             //cout << i + 1<< " -> " ;
             for (int j = 0; j < N; ++j) {
                 if (to_check[j] & (1 << i)) {
                     edges[i].push_back(j);
             //        to_set(to_check[j]);
                 }
             }
            // cout << "\n";
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
                 int ret = prime_condition(L, to_check);
                 cerr << "is prime condition? " << ret << "\n";
                 write_set(L, to_check);
                 return 0;
             }
         }
         //cerr << "MATCHING DONE?";
         return 1;
     }

     void generate_all_sets(int k) {
         if (k == N) {
             do_matching(current_set);
         } else {
             for (int mask = 0; mask < (1 << N); ++mask) {
                 bool flag = false;
                 for (int i = 0; i < k ; ++i) {
                     if (!intersect(mask, current_set[i]) || current_set[i] == mask) {
                         flag = true;
                     }
                 }
                 if (!flag) {
                     current_set.push_back(mask);
                     generate_all_sets(k + 1);
                     current_set.pop_back();
                 }
             }
         }
     }

     bool prime_condition(vector<int>&L, const vector<int>&to_check) {
         for (int i = 0; i < N; ++i) {
             bool flag = true;
             int ret = -1;
             for (int j = 0; j < N; ++j) {
                 if (i == j) {
                     continue;
                 }
                 for (int k = 0; k < N; ++k) {
                     if (intersect(to_check[k], 1<<i) && !intersect(to_check[k], 1<<j)) {
                         ret = j;
                         flag = false;
                     }
                 }
             }
             if (flag) {

                 cout << "fails with pair ( " << i << " " << ret << " )\n";
                 return 0;
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
     void check(vector<int>& to_check) {

         for (int i = 0; i < N; ++i) {
             for (int j = i + 1; j < N; ++j) {
                 bool flag = true;
                 for (int k = 0; k < N; ++k) {
                     if (intersect(to_check[k], 1<<i)) {
                         if (!intersect(to_check[k], 1<<j)) {
                             flag = false;
                         }
                     }
                 }
                 if (flag) {
                     cout << "NO\n";
                     cout << "failed on\n";
                     for (int i = 0; i < N; ++i) {
                         cout << i + 1 << " -> ";
                         to_set(to_check[i]);
                         cout << "\n";
                     }
                     return ;
                 }
             }
         }
         /*
         cout << "succeded on";
         count_set += 1;
         cout << "set: " << count_set << "\n";
         for (int i = 0; i < N; ++i) {
             cout << i + 1 << " -> ";
             to_set(to_check[i]);
             cout << "\n";
         }
         */
     }

     void generate_sets(int k) {
         if (k == N) {
             check(current_set);
         } else {
             for (int mask = 1; mask < (1 << N); ++mask) {
                 if (!(mask & (1 << k))) {
                     continue;
                 }
                 
                 bool flag = false;
                 for (auto s: current_set) {
                     if (!intersect(mask, s) || s == mask) {
                         flag = true;
                     }
                 }
                 if (flag) {
                     continue;
                 } else {
                     current_set.push_back(mask);
                     generate_sets(k + 1);
                     current_set.pop_back();
                 }
             }
         }
     }
     void solve() {
         generate_sets(0);
     }
     void checker() {
         generate_all_sets(0);
     }
};
int main() {
  ifstream cin("test.in");

  int N; cin >> N;
  Solver G(N);
  G.checker();
  return 0;
}

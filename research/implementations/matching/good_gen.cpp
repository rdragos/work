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
    set<vector<int>> unique_sets;

 public:
     Solver(int _N) {
         //
         N = _N;
         count_set = 0;
     }
     bool intersect(int mask1, int mask2) {
         return mask1 & mask2;
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
             cout << Ans[Ans.size() - 1] << "}";
         }
     }
     void check(vector<int>& to_check) {
         /*
         cout << "set: " << count_set << "\n";
         for (int i = 0; i < N; ++i) {
             cout << i + 1 << " -> ";
             to_set(to_check[i]);
             cout << "\n";
         }
         */
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
          //           cout << "fail with pair: " << i + 1 << ", " << j + 1 << "\n";
                     return ;
                 }
             }
         }
         //cout << "PASSED:\n";
         count_set += 1;
         cout << "set: " << count_set << "\n";
         for (int i = 0; i < N; ++i) {
             cout << i + 1 << " -> ";
             to_set(to_check[i]);
             cout << "\n";
         }
         vector<int> tmp(to_check);
         sort(tmp.begin(), tmp.end());
         unique_sets.insert(tmp);
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
         cout << "Found " << count_set << " matchings\n";
         cout << "Found " << unique_sets.size() << " unique sets\n";
     }
};
int main() {
  ifstream cin("test.in");

  int N; cin >> N;
  Solver G(N);
  G.solve();
  return 0;
}

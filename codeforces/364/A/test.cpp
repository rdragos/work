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



bool can(int sum, vector<int>&v) {
  int n = v.size();

  vector<int> used(n, 0);
  for (int i = 0; i < n; ++i) {
    if (used[i]) {
      continue;
    }
    bool flag = false;
    for (int j = i + 1; j < n; ++j) {
      if (!used[j] && v[i] + v[j] == sum) {
        used[i] = used[j] = true;
        flag = true;
        break;
      }
    }
    if (!flag) {
      return false;
    }
  }
  return true;
}
vector<int> recon(int sum, vector<int>&v) {
  int n = v.size(); 
  vector<int> used(n, 0);
  vector<int> pairup(n, -1);

  for (int i = 0; i < n; ++i) {
    if (used[i]) {
      continue;
    }
    for (int j = i + 1; j < n; ++j) {
      if (!used[j] && v[i] + v[j] == sum) {
        used[j] = used[i] = true;
        pairup[i] = j;
        break;
      }
    }
  }
  return pairup;
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N; cin >> N;
  vector <int> v(N);
  for (int i = 0; i < N; ++i) {
    cin >> v[i];
  }
  
  vector<int> ans;
  for (int i = 1; i <= 200; ++i) {
    if (can(i, v)) {
      ans = recon(i, v);
      break;
    }
  }
  for (int i = 0; i < N; ++i) {
    if (ans[i] != -1) {
      cout << i + 1 << " " << ans[i] + 1 << "\n";
    }
  }
  return 0;
}

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


int N = 1e5;
vector <ll> v;

void preproc() {
  v.assign(N + 1, 0);
  for (int i = 1; i <= N; ++i) {
    v[i] = 1LL * i * i * i;
  }
}
int solve(ll x) {
  int total = 0;
  for (int i = N; i >= 1; --i) {
    while(x >= v[i]) {
      x -= v[i];
      total += 1;
    }
  }
  return total;
}
int main() {
  ifstream cin("test.in");
  ofstream cout("test.out");
  ll M; cin >> M;
  preproc();

  vector<vector<int>> f(1001, vector<int>());

  for (int i = 1; i <= 10000; ++i) {
    int r = solve(i);
    f[r].push_back(i);
  }
  for (int i = 1; i <= 1000; ++i) {
    for (auto val: f[i]) {
      cout << val << ", ";
    }
    cout << "\n";
  }
  return 0;
}

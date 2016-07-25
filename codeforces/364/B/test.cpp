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

int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */
  int N, M; cin >> N >> M;
  vector<int> rows(N + 1, 0), cols(N + 1, 0);

  ll ans = 1LL * N * N;
  ll used_rows = 0, used_cols = 0;
  ll hits = 0;

  for (int i = 0; i < M; ++i) {
    int x, y; cin >> x >> y;
    if (rows[x] == 0) {
      hits += N - used_cols;
      used_rows += 1;
      rows[x] = 1;
    }
    if (cols[y] == 0) {
      hits += N - used_rows;
      used_cols += 1;
      cols[y] = 1;
    }
    cout << ans - hits << " ";
  }
  return 0;
}

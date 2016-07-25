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
map <ll, ll> cost;

void solve1(ll v, ll u, ll w) {
  //v != u
  while(v != u) {
    if (v > u) {
      cost[v] += w;
      v >>= 1;
    } else {
      cost[u] += w;
      u >>= 1;
    }
  }
}

ll solve2(ll u, ll v) {
  ll ans = 0;
  while(u != v) {
    if (v > u) {
      ans += cost[v];
      v >>= 1;
    } else {
      ans += cost[u];
      u >>= 1;
    }
  }
  return ans;
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int Q; cin >> Q;
  while(Q--) {
    int op; cin >> op;
    ll v, u, w;
    if (op == 1) {
      cin >> v >> u >> w;
      solve1(v, u, w);
    } else {
      cin >> v >> u;
      cout << solve2(v, u) << "\n";
    }
  }
  return 0;
}

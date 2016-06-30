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

  int N; cin >> N;
  ll K, H; cin >> H >> K;

  vector<ll> v(N);
  for (int i = 0; i < N; ++i) {
    cin >> v[i];
  }


  ll answer = 0;
  ll cur = v[0];
  for (int i = 1; i < N; ++i) {
    if (cur + v[i] <= H) {
      cur += v[i];
    } else {
      ll x = (cur + v[i] - H + K - 1) / K;
      cur = max(0LL, cur - x * K);
      cur += v[i];
      answer += x;

    }
  }
  answer += (cur + K - 1) / K;

  cout << answer << "\n";
  return 0;
}

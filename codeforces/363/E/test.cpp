#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
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
const double eps = 0.00000000001;

int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N, K; cin >> N >> K;
  vector<double> P(N);

  int good = N;
  for (int i = 0; i < N; ++i) {
    cin >> P[i];
    if (P[i] < eps) {
      good--;
    }
  }
  K = min(good, K);
  vector<double> dp(1 << N, 0);
  vector <double> ans(N, 0);
  dp[0] = 1.0;

  for (int i = 0; i < (1 << N); ++i) {
    double sum_prob = 0;
    int cnt = 0;
    for (int bit = 0; bit < N; ++bit) {
      if (i & (1 << bit)) {
        cnt += 1;
        sum_prob += P[bit];
      }
    }

    if (cnt == K) {
      for (int bit = 0; bit < N; ++bit) {
        if (i & (1 << bit)) {
          ans[bit] += dp[i];
        }
      }
    }
    double rem_prob = 1 - sum_prob;
    if (cnt >= K || rem_prob < eps) {
      continue;
    }

    for (int bit = 0; bit < N; ++bit) {
      if (!(i & (1 << bit))) {
        dp[i + (1 << bit)] += dp[i] * P[bit] / rem_prob;
      }
    }
  }
  cout << setprecision(10);
  for (int i = 0; i < N; ++i) {
    cout << ans[i] << " " ;
  }
  return 0;
}

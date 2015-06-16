#include <bits/stdc++.h>

using namespace std;
int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("test.in");
  ofstream cout("test.out");
#endif

  int N; cin >> N;

  vector <int> A(N + 1);
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
  }

  int M; cin >> M;
  vector <int> B(M + 1);
  for (int i = 1; i <= M; ++i) {
    cin >> B[i];
  }

  vector <int> V(N + M + 1);
  for (int i = 1; i <= N + M; ++i) {
    cin >> V[i];
  }
  A[0] = B[0] = -1;

  vector < vector < vector <int> > > dp(N + 1, vector<vector <int>>(M + 1, vector<int>(2, 0)));

  for (int k = 0; k < 2; ++k) {
    dp[0][0][k] = 1;
  }

  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= M; ++j) {

      if (A[i] == V[i + j]) {
        for (int k = 0; k < 2; ++k) {
          dp[i][j][0] = max(dp[i - 1][j][k], dp[i][j][0]);
        }
      }

      if (B[j] == V[i + j]) {
        for (int k = 0; k < 2; ++k) {
          dp[i][j][1] = max(dp[i][j - 1][k], dp[i][j][1]);
        }
      }
    }
  }
  cout << max(dp[N][M][0], dp[N][M][1]);

  return 0;
}

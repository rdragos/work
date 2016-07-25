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
  vector <int> V(N + 1);
  for (int i = 1; i <= N; ++i) {
    cin >> V[i];
  }

  vector <vector <int> > dp(N + 1, vector<int>(4, N + 1));

  dp[0][0] = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j < 3; ++j) {
      dp[i][0] = min(dp[i][0], dp[i - 1][j] + 1);
    }
    for (int j = 1; j < 3; ++j) {
      if (V[i] & (1 << (j - 1))) {
        for (int k = 0; k < 3; ++k) {
          if (k == j) {
            continue;
          }
          dp[i][j] = min(dp[i][j], dp[i - 1][k]);
        }
      }
    }
  }
  /*
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j < 3; ++j) {
      cerr << "( " << j << " , " << dp[i][j] << " ) ";
    }
    cerr << "\n";
  }*/
  int answer = N;
  for (int j = 0; j < 3; ++j) {
    answer = min(answer, dp[N][j]);
  }
  cout << answer << "\n";
  return 0;
}

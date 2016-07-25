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

  vector<string> Mat(N + 1);
  for (int i = 1; i <= N; ++i) {
    cin >> Mat[i];
    Mat[i] = "$" + Mat[i];
  }

  vector<vector<int>> left(N + 2,vector<int>(M + 2, 0));
  vector<vector<int>> right(N + 2,vector<int>(M + 2, 0));
  vector<vector<int>> up(N + 2,vector<int>(M + 2, 0));
  vector<vector<int>> down(N + 2,vector<int>(M + 2, 0));


  int total = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      int cnt = (Mat[i][j] == '*');
      left[i][j] = left[i][j - 1] + cnt;
      up[i][j] = up[i - 1][j] + cnt;
      total += cnt;
    }
  }

  for (int i = N; i >= 1; --i) {
    for (int j = M; j >= 1; --j) {
      int cnt = (Mat[i][j] == '*');
      right[i][j] = right[i][j + 1] + cnt;
      down[i][j] = down[i + 1][j] + cnt;
    }
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      int sum = left[i][j] + right[i][j] + up[i][j] + down[i][j] - 3 * (Mat[i][j] == '*');
      if (sum == total) {
        cout << "YES\n";
        cout << i << " " << j << "\n";
        return 0;
      }
    }
  }
  cout << "NO";
  return 0;
}

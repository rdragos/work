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
  ifstream cin("test.in");
  ofstream cout("test.out");

  int N, T; cin >> N >> T;

  vector<vector<long double>> cant(N + 2,vector<long double>(N + 2, 0));

  cant[1][1] = T;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= i; ++j) {
      cant[i][j] -= 1.0;
      long double t = cant[i][j];
      t = max(0.000L, t);

      cant[i + 1][j] += t / 2.0;
      cant[i + 1][j + 1] += t / 2.0;
    }
  }
  int answer = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= i; ++j) {
      answer += (cant[i][j] >= 0.000000);
      cout << cant[i][j] << " ";
    }
    cout << "\n";
  }
  cout << answer << "\n";
  return 0;
}

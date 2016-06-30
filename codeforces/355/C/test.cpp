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


const int mod = 1e9 + 7;

vector<int> getint(const string &S) {
  vector<int> res(S.size());
  for (int i = 0; i < S.size(); ++i) {
    if (S[i] >= 'a' && S[i] <= 'z') {
      res[i] = S[i] - 'a' + 36;
    } else if (S[i] >= 'A' && S[i] <= 'Z') {
      res[i] = 10 + (S[i] - 'A');
    } else if (S[i] >= '0' && S[i] <= '9') {
      res[i] = 0 + (S[i] - '0');
    } else if (S[i] == '-') {
      res[i] = 62;
    } else {
      res[i] = 63;
    }
  }
  return res;
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  string S; cin >> S;
  int n = S.size();


  vector<int> v = getint(S);

  vector<int> cnt(64, 0);
  for (int i = 0; i < 64; ++i) {
    for (int j = 0; j < 64; ++j) {
      cnt[i & j] += 1;
    }
  }
  ll answer = 1;

  for (int i = 0; i < n; ++i) {
    answer = (1LL * answer * cnt[v[i]]) % mod;
  }
  cout << answer << "\n";
  return 0;
}

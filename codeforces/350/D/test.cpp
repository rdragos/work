#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
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

inline bool check(ll how_many, const vector<ll>& A,
    const vector<ll>& B, ll K) {

  for (int i = 0; i < A.size(); ++i) {
    ll req = A[i] * how_many;
    if (req <= B[i]) {
      continue;
    } else {
      K -= (req - B[i]);
    }
    if (K < 0) {
      return false;
    }
  }
  return true;
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N;
  ll K;
  cin >> N >> K;

  vector <ll> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  vector <ll> B(N);
  for (int i = 0; i < N; ++i) {
    cin >> B[i];
  }


  ll cur_ans = 0;
  for (int bit = 31; bit >= 0; --bit) {
    if (check(cur_ans + (1LL << bit), A, B, K)) {
      cur_ans += (1LL << bit);
    }
  }
  cout << cur_ans;
  return 0;
}

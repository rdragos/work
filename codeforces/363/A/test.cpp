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
const ll INF = 1LL<<32;
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N; cin >> N;
  string S; cin >> S;


  vector <pair <ll, int> > V(N);

  for (int i = 0; i < N; ++i){
    int X; cin >> X;
    V[i] = make_pair(X, S[i] == 'L');
  }

  ll answer = INF;
  sort(V.begin(), V.end());
  ll right = -1;
  for (int i = N - 1; i >= 0; --i) {
    if (V[i].second == 1) {
      right = V[i].first;
    } else {
      if (right == -1) {
        continue;
      }
      answer = min(answer, (right - V[i].first) / 2);
    }
  }

  if (answer == INF) {
    cout << -1;
  } else {
    cout << answer;
  }
  return 0;
}

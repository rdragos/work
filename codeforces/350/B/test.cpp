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
  ll K; cin >> K;

  vector <ll> V(N + 1);

  for (int i = 1; i <= N; ++i) {
    cin >> V[i];
    if (K > i) {
      K -= i;
    } else {
      if (K == i) {
        cout << V[i];
        break;
      } else {
        cout << V[K];
        break;
      }
    }
  }
  return 0;
}

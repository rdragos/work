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
  vector <int> V(N + 1), poz(N + 1, 0);
  for (int i = 1; i <= N; ++i) {
    cin >> V[i];
    poz[V[i]] = i;
  }

  int x1 = max(abs(poz[N] - 1), abs(poz[N] - N));
  int x2 = max(abs(poz[1] - 1), abs(poz[1] - N));

  cout << max(x1, x2);
  return 0;
}

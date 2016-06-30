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

  int N, A; cin >> N >> A;
  vector<int> v(N + 1);

  for (int i = 1; i <= N; ++i) {
    cin >> v[i];
  }

  int answer = v[A];

  for (int i = 1; i <= N; ++i) {
    int x = 0, y = 0;
    int p1 = 0, p2 = 0;

    if (A - i >= 1) {
      p1 = 1;
      x = v[A - i];
    }
    if (A + i <= N) {
      p2 = 1;
      y = v[A + i];
    }
    if (p1 == p2 && p1 == 1) {
      if (x == y && x == 1) {
        answer += 2;
      }
    } else {
      answer += max(x, y);
    }
  }

  cout << answer << "\n";
  return 0;
}

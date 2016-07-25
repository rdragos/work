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

  ll t, s, x; cin >> t >> s >> x;
  if (x < t) {
    cout << "NO";
  } else if (t == x) {
    cout << "YES";
  } else {
    ll times = (x-t) / s;

    for (int i = -1; i <= 1; ++i) {
      if (times + i <= 0) {
        continue;
      }
      if (t + s * (times + i) == x || t + s * (times + i) + 1 == x) {
        cout << "YES";
        return 0;
      }
    }
    cout << "NO";
  }
  return 0;
}

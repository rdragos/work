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

  int N; ll X; cin >> N >> X;

  int distress = 0;

  for (int i = 0; i < N; ++i) {
    char c; cin >> c;
    ll d; cin >> d;
    if (c == '+') {
      X += d;
    } else {
      if (X >= d) {
        X -= d;
      } else {
        distress += 1;
      }
    }
  }

  cout << X << " " << distress << "\n";
  return 0;
}

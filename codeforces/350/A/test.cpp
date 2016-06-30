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


  int mn = N;
  int mx = 0;
  for (int day = 0; day < 7; ++day) {
    int answer = 0;

    for (int i = 1; i <= N; ++i) {
      if ( (day + i) % 7 == 6 || (day + i) % 7 == 5) {
        answer += 1;
      }
    }
    mn = min(mn, answer);
    mx = max(mx, answer);
  }
  cout << mn << " " << mx << "\n";

  return 0;
}

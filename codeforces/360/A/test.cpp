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

  int N, D; cin >> N >> D;


  int ans = 0, seq = 0;
  for (int i = 0; i < D; ++i) {
    string S; cin >> S;

    bool can = false;
    for (int j = 0; j < S.size(); ++j) {
      if (S[j] == '0') {
        can = true;
      }
    }

    if (can == true) {
      seq += 1;
    } else {
      seq = 0;
    }

    ans = max(ans, seq);
  }
  cout << ans << "\n";
  return 0;
}

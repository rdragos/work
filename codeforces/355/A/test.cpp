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

  int N, H; cin >> N >> H;

  int answer = 0;
  for (int i = 0; i < N; ++i) {
    int val; cin >> val;
    answer += (val + H - 1) / H;
  }
  cout << answer << "\n";
  return 0;
}

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


  int N; N = 5;
  vector<int> v(N), cnt(101, 0);

  int s = 0;
  for (int i = 0; i < N; ++i) {
    cin >> v[i];
    cnt[v[i]] += 1;
    s += v[i];
  }

  int answer = s;
  for (int i = 100; i >= 1; --i) {
    if (cnt[i] >= 2) {
      answer = min(answer, s - min(cnt[i], 3) * i);
    }
  }

  cout << answer << "\n";
  return 0;
}

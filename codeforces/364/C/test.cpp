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
  string S; cin >> S;


  set <char> myset;

  for (int i = 0; i < N; ++i) {
    myset.insert(S[i]);
  }

  map<char, int> freq;
  int answer = N;
  for (int i = 0; i < N; ++i) {
    freq[S[i]] = i;

    int mn = N, mx = 0;
    bool flag = true;
    for (auto c: myset) {
      if (freq.find(c) == freq.end()) {
        flag = false;
        break;
      } else {
        mn = min(mn, freq[c]);
        mx = max(mx, freq[c]);
      }
    }
    if (flag == true) {
      answer = min(answer, mx - mn + 1);
    }
  }

  cout << answer << "\n";
  return 0;
}

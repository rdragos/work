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

  int N, K; cin >> N >> K;
  string S; cin >> S;

  int answer = 0;
  vector <char> sel{'a', 'b'};
  for (auto x: sel) {
    queue <int> Q;

    int cur_begin = 0;
    for (int i = 0; i < N; ++i) {
      if (S[i] != x) {
        Q.push(i);
      }
      while(Q.size() > K) {
        int el = Q.front();
        Q.pop();
        cur_begin = el + 1;
      }
      answer = max(answer, i - cur_begin + 1);
    }
  }

  cout << answer << "\n";
  return 0;
}

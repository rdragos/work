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


int get_dig(int n) {
  if (n == 1) {
    return 1;
  }

  int cnt = 0;
  n -= 1;
  while(n > 0) {
    n /= 7;
    cnt += 1;
  }
  return cnt;
}

class Solver {
  vector<int> sol;
  int d1,d2, answer;
  vector<int>vis;
  ll N, M;
  public:
  Solver(int _N, int _M) {
    N = _N;
    M = _M;

    vis.assign(10, 0);

    answer = 0;
  }


  int check() {
    ll x = 0, y = 0;
    for (int i = 0; i < d1; ++i) {
      x = x * 7 + sol[i];
    }
    for (int i = d1; i < d1 + d2; ++i) {
      y = y * 7 + sol[i];
    }
    if (x < N && y < M) {
      //cerr << x << " " << y << "\n";
      return 1;
    } else {
      return 0;
    }
  }

  void back(int k) {
    if (k == d1 + d2) {
      answer += check();
    } else {
      for (int i = 0; i < 7; ++i) {
        if (vis[i] == 0) {
          sol.push_back(i);
          vis[i] = 1;
          back(k + 1);

          vis[i] = 0;
          sol.pop_back();
        }
      }
    }
  }
  int do_task() {
    sol.clear();
    d1 = get_dig(N);
    d2 = get_dig(M);

    back(0);
    return answer;
  }
};
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N, M; cin >> N >> M;
  Solver S(N, M);

  cout << S.do_task() << "\n";
  return 0;
}

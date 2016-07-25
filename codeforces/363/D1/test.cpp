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

struct Point {
  Point() {};

  Point(ll _x, ll _y) {
   x = _x;
   y = _y;
  }

  ll x, y;
};

bool colinear(const Point& a, const Point& b, const Point& c) {
  ll area = (b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y);
  if (area != 0) {
    return false;
  } else {
    if (a.x == b.x) {
      if (a.y <= b.y && b.y <= c.y) {
        return true;
      } else if (a.y >= b.y && b.y >= c.y) {
        return true;
      } else {
        return false;
      }
    } else {
      if (a.x <= b.x && b.x <= c.x) {
        return true;
      } else if (a.x >= b.x && b.x >= c.x) {
        return true;
      } else {
        return false;
      }
    }
  }
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int K, N; cin >> K >> N;

  vector <Point> Gate(K);
  for (int i = 0; i < K; ++i) {
    int x, y; cin >> x >> y;
    Gate[i] = Point(x, y);
  }

  vector <Point> V(N);
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    V[i] = Point(x, y);
  }


  vector<int> neigh[K][N];

  for (int k = 0; k < K; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (i == j) {
          continue;
        }
        // check if j gets in the path between Gate[k] and V[i]
        if (colinear(Gate[k], V[j], V[i])) {
          neigh[k][i].push_back(j);
        }
      }
    }
  }

  vector<int> vis(N, -1);
  vector<int> Q(10, 0);

  int answer = 0;
  int cur_cnt = 0;
  for (int i = 0; i < N; ++i) {
    vector<int> perm;
    for (int k = 0; k < K; ++k) {
      perm.push_back(k);
    }
    do {
      bool flag = false;

      int front, back;
      front = back = 0;
      Q[back] = i;
      vis[i] = ++cur_cnt;
      for (int k = 0; k < K && !flag; ++k) {
        if (front > back) {
          break;
        }
        int el = Q[front++];
        for (auto node: neigh[perm[k]][el]) {
          if (vis[node] != cur_cnt) {
            Q[++back] = node;
            vis[node] = cur_cnt;
            if (back >= K) {
              flag = true;
              break;
            }
          }
        }
      }
      if (flag == false) {
        answer += 1;
        break;
      }
    } while(next_permutation(perm.begin(), perm.end()));
  }
  cout << answer << "\n";
  return 0;
}

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

struct Cell {
  int x, y;
  Cell() {}
  Cell(int _x, int _y) {
    x = _x;
    y = _y;
  }
  bool operator < (const Cell& other) const {
    if (x == other.x) {
      return y < other.y;
    } else {
      return x < other.x;
    }
  }
};

map<Cell, vector<Cell>> edges;


bool check_latin(vector<vector<int>> square) {
  for (int i = 0; i < 10; ++i) {
    vector<int> vis(10, 0);
    for (int j = 0; j < 10; ++j) {
      if (square[i][j] == -1) {
        continue;
      }
      if (vis[square[i][j]]) {
        return 0;
      }
      vis[square[i][j]] = 1;
    }
  }

  for (int j = 0; j < 10; ++j) {
    vector<int> vis(10, 0);
    for (int i = 0; i < 10; ++i) {
      if (square[i][j] == -1) {
        continue;
      }
      if (vis[square[i][j]]) {
        return 0;
      }
      vis[square[i][j]] = 1;
    }
  }
  return 1;
}
vector<vector<int>> gen_square(vector<int> perm) {
  vector<vector<int>> err(0);
  vector<vector<int>> answer(10, vector<int>(10, -1));

  for (int i = 0; i < 10; ++i) {
    answer[i][0] = perm[i];
  }

  for (int i = 0; i < 10; ++i) {
    Cell c(i, 0);
    for (auto neigh: edges[c]) {
      int x = neigh.x;
      int y = neigh.y;

      if (answer[x][y] == -1) {
        answer[x][y] = answer[i][0];
      } else if (answer[x][y] != answer[i][0]) {
        return err;
      }
    }
  }

  return answer;
}

void write(vector<vector<int>> square) {
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      cout << square[i][j] << " " ;
    }
    cout << "\n";
  }
}
int main() {
  ifstream cin("test.in");
  ofstream cout("test.out");

  /*
  for (int i = 0; i < 10; ++i) {
    if (i == 3 || i == 4) {
      continue;
    }
    for (int j = 0; j < 10; ++j) {
      if (j == 3 || j == 4) {
        continue;
      }
      if (i == j) {
        continue;
      }
      cout << i << j << 3 << 4 << "\n";
    }
  }
  */

  string S;
  int val;
  vector<vector<Cell>> all(10, vector<Cell>());
  while(cin >> S >> val) {
    int x = S[0] - '0';
    int y = S[1] - '0';
    Cell C(x, y);
    all[val].push_back(C);
  }

  for (int i = 0; i < 10; ++i) {
    cerr << "val: " << i << " " ;
    for (int j = 0; j < all[i].size(); ++j) {
      cerr << "(" << all[i][j].x << ", " << all[i][j].y << ") ; ";
      for (int k = 0; k < all[i].size(); ++k) {
        edges[all[i][j]].push_back(all[i][k]);
      }
    }
    cerr << "\n";
  }

  for (int i = 0; i < 10; ++i) {
    Cell c(i, 0);
    cerr << "neighbours with: " << i << "\n";
    for (auto neigh: edges[c]) {
      cerr << "(" << neigh.x << " " << neigh.y << ") ; ";
    }
    cerr << "\n";
  }

  vector<int> perm;
  for (int i = 0; i < 10; ++i) {
    perm.push_back(i);
  }
  int cnt = 0;
  vector<vector<vector<int>>> allsquares;
  do {
    vector<vector<int>> square = gen_square(perm);
    if (square.size() != 0) {
      //latin square?
      if (check_latin(square)) {
        allsquares.push_back(square);
        cnt += 1;
        //write(square);
      }
    }
  } while(next_permutation(perm.begin(), perm.end()));
  write(allsquares[0]);
  cout << cnt << "\n";
  return 0;
}

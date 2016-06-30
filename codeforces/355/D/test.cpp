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



struct Coord {
  int x, y;
  Coord() {}
  Coord(int _x, int _y) {
    x = _x; y = _y;
  }
  int distance(const Coord&other) {
    return abs(other.x - x) + abs(other.y - y);
  }
};

struct Node {
  Node() {};
  Node(int _x, int _y, int _l) {
    x = _x;
    y = _y;
    level = _l;
  }

  int x, y, level;
};

inline bool inside(int x, int y, int n, int m) {
  return 0 <= x && x < n && 0 <= y && y < m;
}
int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N, M, P;
  cin >> N >> M >> P;

  vector <vector <int> > table(N, vector<int>(M, 0));
  vector<vector<Coord>> allCells(P + 1, vector<Coord>());
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cin >> table[i][j];
      allCells[table[i][j]].push_back(Coord(i, j));
    }
  }

  allCells[0].push_back(Coord(0,0));

  vector<vector<int>> dp(N,vector<int>(M, 1<<29));
  for (auto &cell: allCells[1]) {
    dp[cell.x][cell.y] = cell.distance(Coord(0,0));
  }
  for (int i = 2; i <= P; ++i) {
    if (allCells[i].size() * allCells[i - 1].size() <= N * M) {
//      cerr << "step " << i << " hard " << "\n";
      for (auto& cell1: allCells[i - 1]) {
        for (auto& cell2: allCells[i]) {
          dp[cell2.x][cell2.y] = min(dp[cell2.x][cell2.y], dp[cell1.x][cell1.y] + cell1.distance(cell2));
        }
      }
    } else {
      cerr << "bfs?";
      //do bfs
      queue <Coord> Q;

      vector<vector<int>> vis(N,vector<int>(M, -1));
      for (auto& cell: allCells[i - 1]) {
        Q.push(cell);
        vis[cell.x][cell.y] = dp[cell.x][cell.y];
      }

      while(!Q.empty()) {
        Coord cur = Q.front();
        Q.pop();
        for (int k = 0; k < 4; ++k) {
          int xn = cur.x + dx[k];
          int yn = cur.y + dy[k];

          if (!inside(xn, yn, N, M)) {
            continue;
          }

          if (vis[xn][yn] == -1 || (vis[xn][yn] > vis[cur.x][cur.y] + 1)) {
            vis[xn][yn] = vis[cur.x][cur.y] + 1;
            Q.push(Coord(xn, yn));
          }
        }
      }
      for (auto& cell: allCells[i]) {
        dp[cell.x][cell.y] = vis[cell.x][cell.y];
      }
    }
  }

  Coord fl = allCells[P][0];
  cout << dp[fl.x][fl.y];

  return 0;
}

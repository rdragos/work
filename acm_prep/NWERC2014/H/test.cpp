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


class Graph {
  vector <vector <int>> edges;
  vector <pair <int, int> > answer;
  vector <int> visited;
  int p, N;
  private:
    void df(int node) {
      visited[node] = 1;
      for (auto &vec: edges[node]) {
        if (!visited[vec]) {
          answer[vec].first = answer[node].second;
          answer[vec].second = ++p;
          df(vec);
        }
      }
    }
  public:
    Graph(int _N): edges(_N), answer(_N), visited(_N, 0), p(2){N = _N;}
    void addEdge(int x, int y) {
      edges[x].push_back(y);
      edges[y].push_back(x);
    }
    void solve() {
      answer[0].first = 1;
      answer[0].second = 2;
      df(0);
      for (int i = 0;  i < N; ++i) {
        cout << answer[i].first << " " << answer[i].second << "\n";
      }
    }
};
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */
  int N; cin >> N;

  Graph G(N);
  for (int i = 0; i < N - 1; ++i) {
    int x, y; cin >> x >> y;
    x -= 1; y -= 1;
    G.addEdge(x, y);
  }
  G.solve();
  return 0;
}

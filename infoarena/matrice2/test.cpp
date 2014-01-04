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

const int MAXN = 305;

using namespace std;

int T[MAXN * MAXN];
int matrix[MAXN][MAXN];
class nodeMatrix {
  public:
    int x, y, val;
    nodeMatrix() {
        x = y = val = 0;
    }
    nodeMatrix(int _x, int _y, int _val) {
        x = _x; y = _y; val = _val;
    }
    bool operator > (const nodeMatrix &other) const {
        return val > other.val;
    }
};
class nodeQuery {
  public:
      int x1, y1, x2, y2;
      int id, val;
      nodeQuery() {
          x1 = y1 = x2 = y2 = id = 0;
      }
      nodeQuery(int _x1, int _y1, int _x2, int _y2, int _id) {
          x1 = _x1; y1 = _y1;
          x2 = _x2; y2 =_y2;
          id = _id;
      }
      bool operator > (const nodeQuery& other) const { 
          return val > other.val;
      }
};

inline int find(int x) {
    if (T[x] == x) {
        return x;
    }
    return (T[x] = find(T[x]));
}
inline bool is_connected(int x, int y) {
    return T[find(x)] == T[find(y)];
}

void unite(int x, int y) {
    int r = rand() % 2;
    if (r & 1) {
        T[find(x)] = find(y);
    } else {
        T[find(y)] = find(x);
    }
}
inline bool check(int x, int y, const int& N) {
    return (0 <= x && x < N && 0 <= y && y < N);
}
inline void insert(const nodeMatrix& v, const int& N) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int dir1 = v.x + dx[i];
        int dir2 = v.y + dy[i];
        if (check(dir1, dir2, N)) {
            if (matrix[dir1][dir2] >= matrix[v.x][v.y]) {
                unite(v.x * N + v.y, dir1 * N + dir2);
            }
        }
    }
}
int main() {
    freopen("matrice2.in", "r", stdin);
    freopen("matrice2.out", "w", stdout);
    
    srand(time(NULL));    
    int N, Q;
    cin >> N >> Q;

    vector <nodeMatrix> p(N * N);
    vector <nodeQuery> query(Q);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x; cin >> x; 
            matrix[i][j] = x;
            p[i * N + j] = nodeMatrix(i, j, x);
        }
    }
    
    for (int i = 0; i < Q; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        --x1; --y1; --x2; --y2;
        query[i] = nodeQuery(x1, y1, x2, y2, i);
    }
    sort(p.begin(), p.end(), greater<nodeMatrix>());
     
    for (int step = 20; step >= 0; --step) {
        sort(query.begin(), query.end(), greater<nodeQuery>());
        
        for (size_t i = 0; i < p.size(); ++i) {
            T[i] = i;
        }

        int current = 0;

        for (size_t i = 0; i < p.size(); ++i) {
            insert(p[i], N);
            if (i * i != p.size() - 1) {
               if (p[i].val == p[i + 1].val) {
                  continue;
               }
            } 
            while (current < Q && (i == p.size() - 1 || (query[current].val + (1 << step)) >= p[i + 1].val)) {
                int x1 = query[current].x1, y1 = query[current].y1;
                int x2 = query[current].x2, y2 = query[current].y2;

                if (is_connected(x1 * N + y1, x2 * N + y2)) {
                    query[current].val += (1 << step);
                }
                current += 1;
            }
        }
    }
    vector <int> answer(Q);
    for (int i = 0; i < Q; ++i) {
        answer[query[i].id] = query[i].val + 1;
    }

    for (int i = 0; i < Q; ++i) {
        cout << answer[i] << "\n";
    }    
    return 0;
}

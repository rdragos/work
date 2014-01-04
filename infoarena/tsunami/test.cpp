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

int dx[4] = {0 , 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

inline bool in_matrix(int x, int y, const int& N, const int& M) {
    return (0 <= x && 0 <= y && x < N && y < M);
}
void BF(int x, int y, const vector <vector <int> > &A, 
        vector <vector <int> > &visited, const int &H) {
    queue <pair <int, int> > Q;
    Q.push(make_pair(x, y));
    visited[x][y] = 1;

    while(!Q.empty()) {
        int xn = Q.front().first;
        int yn = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; ++i) {
            int xn2 = xn + dx[i];
            int yn2 = yn + dy[i];
            if (in_matrix(xn2, yn2, A.size(), A[0].size())) {
                if (!visited[xn2][yn2] && H > A[xn2][yn2] && A[xn2][yn2] != 0) {
                    Q.push(make_pair(xn2, yn2));
                    visited[xn2][yn2] = 1;
                }
            }
        }
    }
}
int main() {
    ifstream cin("tsunami.in");
    ofstream cout("tsunami.out");
    
    int N, M, H;
    cin >> N >> M >> H;

    vector <vector <int> > A(N, vector <int>(M) );
    vector <vector <int> > visited(N, vector <int>(M, 0));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (A[i][j] != 0) {
                continue;
            }
            for (int k = 0; k < 4; ++k) {
                int x = i + dx[k];
                int y = j + dy[k];
                if (in_matrix(x, y, N, M)) {
                    if (A[x][y] < H && A[x][y] != 0 && !visited[x][y]) {
                        BF(x, y, A, visited, H);
                    }
                }
            }
        }
    }
    int answer = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            answer += visited[i][j];
        }
    }

    cout << answer << "\n";
    return 0;
}

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
 
 
const int INF = 1 << 30;

class Solver {
 
    vector < vector <int> > table;
    vector < vector <int> > tableMax;
    vector <int> lg;
    public:
        Solver(int N, const vector <int> &v): table(17, vector <int>(N, INF)),tableMax(17, vector <int>(N, -INF)), lg(N + 1) {
            //preprocess log
            lg[1] = 0;
            for (int i = 2; i <= N; ++i) {
                lg[i] = lg[i >> 1] + 1;
            }
            for (int i = 0; i < N; ++i) {
                table[0][i] = v[i];
                tableMax[0][i] = v[i];

            }

            for (int len = 1; len < 17; ++len) {
                for (int i = 0; i < N; ++i) {
                    table[len][i] = table[len - 1][i];
                    tableMax[len][i] = tableMax[len - 1][i];

                    if (i + (1 << (len - 1)) < N) {
                        table[len][i] = min(table[len][i], table[len - 1][i + (1 << (len - 1))]);
                        tableMax[len][i] = max(tableMax[len][i], tableMax[len - 1][i + (1 << (len - 1) )] );
                    }
                }
            }
        }
        inline int queryMin(int x, int y) { 
            int len = lg[y - x + 1];
            return min(table[len][x], table[len][y - (1 << len) + 1]);
        }
        inline int queryMax(int x, int y) {
            int len = lg[y - x + 1];
            return max(tableMax[len][x], tableMax[len][y - (1 << len) + 1] ) ;
        }
};
 

inline long long calc(Solver& R, int how_many, int len, int N, vector <int>& v) {
    long long answer = 0;
    for (int start = 0; start < len; ++start) {
        long long temp = 0; 
        for (int i = start, piece = 0; piece < how_many; ++piece, i += len) {
            temp += R.queryMax(i, i + len - 1) - R.queryMin(i, i + len - 1) ;
        }
        answer = max(answer, temp);
    }
    return answer;
}

int main() {
    ifstream cin("collar.in");
    ofstream cout("collar.out");
     
    int N; cin >> N;
    vector <int> v(N * 2);
    for (int i = 0; i < N; ++i) {
        cin >> v[i];
        v[N + i] = v[i];
    }
    N *= 2;
    Solver R(N, v);
    
    long long answer = -INF;
    
    N /= 2;
    for (int len = 1; len * len <= N; ++len) {
        if (N % len) {
            continue;
        }

        
        long long t1 = calc(R, N / len, len, N, v);
        long long t2 = calc(R, len, N / len, N, v);
        cerr << len << " " << N / len << " " << t1 << " " << t2 << "\n";
        answer = max(answer, max(t1, t2));
    
    }
    cout << answer << "\n";
    return 0;
}

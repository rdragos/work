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


class Solver {

    vector < vector <int> > table;
    vector <int> lg;
    public:
        Solver(int N, const vector <int> &v): table(18, vector <int>(N, 1 << 25)), lg(N + 1) {
            //preprocess log
            lg[1] = 0;
            for (int i = 2; i <= N; ++i) {
                lg[i] = lg[i >> 1] + 1;
            }
            for (int i = 0; i < N; ++i) {
                table[0][i] = v[i];
            }
            for (int len = 1; len < 18; ++len) {
                for (int i = 0; i < N; ++i) {
                    table[len][i] = table[len - 1][i];
                    if (i + (1 << (len - 1)) < N) {
                        table[len][i] = min(table[len][i], table[len - 1][i + (1 << (len - 1))]);
                    }
                }
            }
        }
        int query(int x, int y) {
            int len = lg[y - x + 1];
            return min(table[len][x], table[len][y - (1 << len) + 1]);
        }
};

int main() {
    ifstream cin("rmq.in");
    ofstream cout("rmq.out");
    
    int N, Q; cin >> N >> Q;

    vector <int> v(N);
    for (int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    Solver R(N, v);
    for (int i = 0; i < Q; ++i) {
        int a, b; cin >> a >> b;
        cout << R.query(a - 1, b - 1) << "\n";
    }
    return 0;
}

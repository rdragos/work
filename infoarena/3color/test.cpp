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
    ifstream cin("3color.in");
    ofstream cout("3color.out");
    
    int N, V; cin >> N >> V;
    vector <int> X(V), Y(V);

    vector <vector <int> > G(N, vector <int>());
    vector <int> sel(N, 0);

    for (int i = 0; i < V; ++i) {
        cin >> X[i] >> Y[i];
        G[X[i]].push_back(Y[i]);
        G[Y[i]].push_back(X[i]);
    }

    for (int i = 0; i < N; ++i) {
        bool ok = 0;
        for (int col = 1; col <= 100 && !ok; col++) {
            int t = 1;
            for (auto &it : G[i]) {
                if (sel[it] == col) {
                    t = 0;
                }
            }
            sel[i] = col;
            ok |= t;
            
        }
    }
    for (int i = 0; i < N; ++i) {
        cout << sel[i] - 1<< " " ;
    }

    return 0;
}

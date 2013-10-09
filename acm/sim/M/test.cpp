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

const int MAXN = 200005;

using namespace std;


int C[MAXN];
int D[MAXN];
int last[MAXN];

int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    int N;
    cin >> N;
    
    memset(D, 1 << 30, sizeof(D));
    
    D[0] = 0;

    for (int i = 1; i <= N; ++i) {
        cin >> C[i];
        D[i] = D[i - 1] + 1;
        if (last[C[i]] > 0) {
            D[i] = min(D[i], D[last[C[i]]] + 1);
        }
        last[C[i]] = i;
    }
    
    cout << D[N] - 1<< "\n";

    return 0;
}

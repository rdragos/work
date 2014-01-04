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

const int MAXN = 500005;
using namespace std;


int CNT = 1;
int poz[MAXN], RSD[MAXN], SRD[MAXN];
int ansLeft[MAXN], ansRight[MAXN];

int solve(int left, int right) {
    if (left > right) {
        return 0;
    }
    CNT += 1;
    int p = CNT;
    ansLeft[RSD[p]] = solve(left, poz[RSD[p]] - 1);
    ansRight[RSD[p]] = solve(poz[RSD[p]] + 1, right);
    
    return RSD[p];
}

int main() {
    ifstream cin("curatenie.in");
    ofstream cout("curatenie.out");

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> SRD[i];
        poz[SRD[i]] = i;
    }
    for (int i = 1; i <= N; ++i) {
        cin >> RSD[i];
    }
    for (int i = 1; i <= N; ++i) {
        if (SRD[i] == RSD[1]) {
            ansLeft[RSD[1]] = solve(1, i - 1);
            ansRight[RSD[1]] = solve(i + 1, N);
        }
    }
    for (int i = 1; i <= N; ++i) {
        cout << ansLeft[i] << " " << ansRight[i] << "\n";
    }
    return 0;
}

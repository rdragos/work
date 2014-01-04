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
#include <cmath>
#include <iomanip>
#define pb push_back

#define mp make_pair
#define x first
#define y second
#define ll long long

using namespace std;

ll p_dist(pair <int, int> p1, pair <int, int> p2) {
    return 1LL * (p2.x - p1.x) * (p2.x - p1.x) + 1LL * (p2.y - p1.y) * (p2.y - p1.y) ;
}
ll solve(int st, int dr, const vector <pair <int, int> > &P, vector <pair <int, int> > &Y) {
    if (st > dr || st == dr) {
        return 1LL << 62;
    }
    if (dr - st == 1) {
        return p_dist(P[st], P[dr]);
    }
    int mid = (st + dr) / 2;
    ll d = min(solve(st, mid - 1, P, Y) , solve(mid, dr, P, Y));
    
    int m = mid, p = 0, i;
    vector <pair <int, int> > v(dr - st + 1);
    
    for (i = st; i < mid && m <= dr; ++i) {
        if (Y[i] < Y[m]) {
            v[p++] = Y[i];
        } else {
            v[p++] = Y[m];
            ++m;
        }
    }
    for (; i < mid; ++i) {
        v[p++] = Y[i];
    }
    for(; m <= dr; ++m) {
        v[p++] = Y[m];
    }
    for (int i = 0; i < p; ++i) {
        for (int j = i + 1; j < p && (j - i) < 7; ++j) {
            d = min(d, p_dist(v[i], v[j]));
        }
    }
    p = 0;
    for (int i = st; i <= dr; ++i)
        Y[i] = v[p++];

    return d;
}
int main() {
    ifstream cin("cmap.in");//freopen("cmap.in", "r", stdin);
    ofstream cout("cmap.out");//freopen("cmap.out", "w", stdout);
    
    int N; cin >> N;
    vector <pair <int, int> > P(N);
    vector <pair <int, int> > Y(N);

    for (int i = 0; i < N; ++i) {
        cin >> P[i].first >> P[i].second;
    } 
    sort(P.begin(), P.end());
    
    for (int i = 0; i < N; ++i) {
        Y[i] = P[i];
    }
    
    cout << setprecision(20) << sqrt(solve(0, P.size() - 1, P, Y));
    return 0;
}

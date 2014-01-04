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
#include <cassert>

#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long


#define fs (2 * mid)
#define fd (2 * mid + 1)

const int MAXN = 100000;

using namespace std;

int aint[1 << 18];

inline bool cmp(const pair <int, int> &p1, const pair <int, int> &p2) {
    return (p1.first == p2.first) ? p1.second > p2.second : p1.first < p2.first;
}
inline int query(int node, int left, int right, int pos) {    
     
    if(right <= pos) {
        return aint[node];
    }
    int mid = (left + right) / 2;
    int ansRight = 0;
     
    if(pos > mid) {
        ansRight = query(fd, mid + 1, right, pos);
    }
    
    return max(ansRight, query(fs, left, mid, pos));
}  

inline void update(int node, int left, int right, int pos, int val) {
    if(left == right) {
        aint[node] = max(aint[node], val);
        return ;
    }
    int mid = (left + right) / 2;

    if(pos > mid) {
        update(fd, mid + 1, right, pos, val);
    }
    if(pos <= mid) {
        update(fs, left, mid, pos, val);
    }
    aint[node] = max(aint[fs], aint[fd]);
}

int main() {
    ifstream cin("plicuri.in");
    ofstream cout("plicuri.out");

    vector <pair <int, int> > v;

    int N; cin >> N;
    assert(1 <= N && N <= 100000);

    for (int i = 1; i <= N; ++i) {
        int L, W; cin >> L >> W;
        
        assert(1 <= L && L <= 100000);
        assert(1 <= W && W <= 100000);

        v.push_back(make_pair(min(L, W), max(L, W)));
    }

    sort(v.begin(), v.end(), cmp);
     
    int sol = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        int qtemp;
        if(v[i].second == 1) {
            qtemp = 1;
        } else {
            qtemp = query(1, 1, MAXN, v[i].second - 1) + 1;
        }
        //cerr << v[i].second << " " << qtemp << "\n";    
        update(1, 1, MAXN, v[i].second, qtemp );   
        sol = max(sol, qtemp);

        //cout << aint[1] << "\n";
    }
    cout << sol << "\n";
    return 0;
}

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
const ll MOD = 1e9 + 7;

using namespace std;


ll lg_put(ll A, ll B) {
    ll R = 1;
    for (int i = 0; (1LL << i) <= B; ++i) {
        if (B & (1LL << i)) {
            R = R * A;
            if(R >= MOD) {
                R %= MOD;
            }
        }
        A = A * A;
        if(A >= MOD) {
            A %= MOD;
        }
    }
    return R;

}
int main() {
    freopen("frumoasa.in", "r", stdin);
    freopen("frumoasa.out", "w", stdout);
    
    ll N, P, sol = 1;
    cin >> N >> P;

    assert(1 <= N && N <= 1e15);
    assert(1 <= P && P <= N);

    if (P >= 26) {
        sol = 0;
    } else {
        ll act, prev = 1;
        for (int i = 1; i <= P; ++i) {
            act = prev * (26 - i + 1);
            if (act >= MOD) {
                act %= MOD;
            }
            prev = act;
        }
        sol = (lg_put(26 - P, N - P) * act) % MOD;
    }
    cout << sol << "\n";
    return 0;
}

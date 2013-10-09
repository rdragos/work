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
/*    
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    int N, M; 
    cin >> N >> M;
    
    ll ans = 0;

    int step = 1;

    for (int i = 1; i <= M; ++i) {
        int T; cin >> T;
        if (T >= step) {
            ans += T - step;
        } else {
            ans += N - step + T;
        }
        step = T;
    }
    cout << ans << "\n";
    return 0;
}

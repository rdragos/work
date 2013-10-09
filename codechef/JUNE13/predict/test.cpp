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
#include <iomanip>
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    
    int T;
    double P;

    for (cin >> T; T--; ) {
        cin >> P; 
        double P1 = P, P2 = (1.0 - P1);

        double ans = 2.0 * P1 * P2 * 10000.0;
        ans += 10000.0 * P1;  
        cout << setprecision(7) << ans << "\n";
    }
    return 0;
}

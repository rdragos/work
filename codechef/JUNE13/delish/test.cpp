#include <cstdio>
#include <vector>
#include <iostream>

#define i64 long long

const i64 INF = 1e10;
const int MAXN = 10005;
using namespace std;

i64 left_max[MAXN], left_min[MAXN], right_max[MAXN], right_min[MAXN];
i64 A[MAXN];

int N;

inline i64 solve() {
    cin >> N;
//  todo : initialize good left/right_min/max at both ends
    //shazam
    
    i64 ans = -INF;    
    left_max[0] = -INF;
    left_min[0] = INF;

    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }

    i64 S = 0;
    i64 Smin = 0, Smax = 0;

    for (int i = 1; i <= N; ++i) {
        S += A[i];
        left_max[i] = left_max[i - 1];
        left_min[i] = left_min[i - 1];

        if (S - Smin > left_max[i]) {
            left_max[i] = S - Smin;
        }
        if (S - Smax < left_min[i]) {
            left_min[i] = S - Smax;
        }

        Smin = min(Smin, S);
        Smax = max(Smax, S);
    }
    
    Smin = Smax = 0;
    S = 0;
    
    right_max[N + 1] = -INF;
    right_min[N + 1] = INF;

    for (int i = N; i >= 1; --i) {
        S += A[i];
        
        right_max[i] = right_max[i + 1];
        right_min[i] = right_min[i + 1];

        if (S - Smin > right_max[i]) {
            right_max[i] = S - Smin;
        }
        if (S - Smax < right_min[i]) {
            right_min[i] = S - Smax;
        }
        Smin = min(S, Smin);
        Smax = max(S, Smax);
    }
    for (int i = 1; i < N; ++i) {
        ans = max(ans, left_max[i] - right_min[i + 1]);
    }
    for (int i = N; i > 1; --i) {
        ans = max(ans, right_max[i] - left_min[i - 1]);
    }
    
    return ans;
}
int main() {
//    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
    
    int T;
    for (cin >> T; T--; ) {
        cout << solve() << "\n";
    }

    return 0;
}

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

const int MAXN = 100;
using namespace std;

int A[MAXN];

int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/
    int N, M;

    cin >> N >> M;

    for (int i = 1; i <= M; ++i)
        cin >> A[i];
    sort(A + 1,A + M + 1);

    int ans = 1 << 30;

    for (int i = 1; i + N - 1<= M; ++i) {
        ans = min(ans, A[i + N - 1] - A[i]);
    }
    cout << ans << "\n";

    return 0;
}

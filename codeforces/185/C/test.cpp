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

#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;

int N, K;

int main() {
//    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
    
    cin >> N >> K;
    
    int cnt = 0;

    for (int i = 1; i <= N; ++i)
        cnt += (N - i);
    if (K >= cnt) {
        printf("no solution\n");
        return 0;
    }
    cerr << cnt << "\n";   
    int LIM = 100000;

    for (int i = LIM ; i > LIM - N; --i) {
        printf("%d %d\n", 0, i);
    }
    return 0;
}

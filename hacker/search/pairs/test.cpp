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
#include <unordered_map>

#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long

const int MAXN = 100003;
using namespace std;
/*
ifstream fin("test.in");
ofstream fout("test.out");
*/
unordered_map<int,int> H;
int main() {

    int A[MAXN];    
    int N, K;

    cin >> N >> K;
    
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        H[A[i]] += 1;
    }
    int ans = 0;

    for (int i = 1; i <= N; ++i)
        ans += (H[A[i]- K]);
    cout << ans << "\n";
    return 0;
}

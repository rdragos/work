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

const int MAXN = 100005;

using namespace std;

int A[MAXN];
int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/
    int N; cin >> N;

    int ans = 0;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        if (A[i] == i) {
            ++ans;
        }
    }

    int p = 0;
    for (int i = 0; i < N; ++i) {
        if (A[i] != i) {
            int j = A[i];

            if (A[j] != j) {
                p = max(p, 1);
                if(A[j] == i) {
                    p = max(p, 2);
                }
            }
        }
    }
    
    cout << ans + p << "\n";
    return 0;
}

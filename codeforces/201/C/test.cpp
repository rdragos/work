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


const int MAXN = 105;
using namespace std;

int A[MAXN];

int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    int N; cin >> N;

    for (int i = 0; i < N; ++i)
        cin >> A[i];
    
    sort(A, A + N);

    int nr = A[0];

    for (int i = 1; i < N; ++i)
        nr = __gcd(A[i], nr);

    int ans = (A[N - 1] / nr) - N;
    
    if (ans & 1) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }

    return 0;
}

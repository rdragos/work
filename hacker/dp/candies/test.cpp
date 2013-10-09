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
#define lllong long


const int MAXN = 100010;
using namespace std;

int L[MAXN], R[MAXN];
int A[MAXN];
long long sum;
int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/
    int N; cin >> N;

    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    
    R[N] = 1;
    for (int i = N - 1; i >= 1; --i)
        if (A[i] > A[i + 1])
            R[i] = R[i + 1] + 1;
        else R[i] = 1;
    L[1] = 1;
    for (int i = 2; i <= N; ++i)
        if (A[i] > A[i - 1])
            L[i] = L[i - 1] + 1;
        else L[i] = 1;
    
    for (int i = 1; i <= N; ++i) {
//        cerr << L[i] << " " << R[i] << "\n";
        sum += max(L[i], R[i]);
    }
    
    cout << sum << "\n";
            
    return 0;
}

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

int A[20];

int dec(int nr, int ok) {
    
    A[0] = 0;

    while(nr > 0) {
        A[++A[0]] = nr % 10;
        nr /= 10;
    }
    int s = 0;

    for (int i = 1; i <= A[0]; ++i)
        s += A[i];
    if (ok == 0)
        return s;

    s = 0;
    
    for (int i = 1; i <= A[0]; ++i)
        s += A[i] * A[i];

    return s;
}
inline bool prime(int nr) {
    if (nr == 1) {
        return 0;
    }

    for (int i = 2; i * i <= nr; ++i)
        if (nr % i == 0)
            return 0;
    return 1;
}

int main() {
    ifstream cin("test.in");
    ofstream cout("test.out");
    
    int N; cin >> N;
    
    int cnt = 0;
    for (int i = 1; i <= N; ++i) {
        int X = dec(i,0);
        int Y = dec(i,1);
        if(prime(X) && prime(Y)) {
            cnt += 1;
        }
    }
    cout << cnt;
    return 0;
}

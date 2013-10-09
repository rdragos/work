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
    ll A, B;
    ll sol = 0;
    cin >> A >> B;

    while(A != 0 && B != 0) {
//        cerr << A << " " << B << "\n";
        if (A >= B) {
            sol += A / B;
            A = A % B;
        }
        else if (B > A) {
            sol += B / A;
            B = B % A;
        }
    }

    cout << sol << "\n";
    
    return 0;
}

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
    ll x,y,a,b,d, mul;
    cin >> x >> y >> a >> b;
    d = __gcd(x,y);
    mul = 1LL * x * y / d;
    cout << b/mul - (a-1)/mul;
    return 0;
}

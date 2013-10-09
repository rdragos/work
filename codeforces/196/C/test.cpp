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

const ll mod = 1000000009;
using namespace std;


int mpow(ll a, ll b) {
    ll r = 1;
    while(b > 0) {
        if (b & 1)
            r = (r * a) % mod;
        b /= 2;
        a = (a * a) % mod;
    }
    return r;
}

int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    ll n, m, k;
    ll dtime, shit, to_add;

    cin >> n >> m >> k;

    dtime = max(m - (n - n/k),0LL);
    if (dtime == 0) {
        cout << (n - n / k) % mod;
        return 0;
    }

    shit = n - k * dtime;
    
    to_add = m - dtime * k;
    
    ll res = (k%mod * (mpow(2,dtime) + (mpow(2,dtime-1)-1+mod) * (k+1)%mod )  %mod) % mod;
    
    cout << (res + to_add) % mod;

    return 0;
}

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


void swap(ll &a, ll &b) {
    ll aux = a;
    a = b;
    b = aux;
}

void swaping(ll &a, ll &b, ll &c) {
    if (a > b && a > c) {
        swap(a,c);
    }
    if (b > a && b > c) {
        swap(b,c);
    }
}
ll getd(ll x1, ll y1, ll x2, ll y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}
int main() {
/*    
    ifstream cin("test.in");
    ofstream cout("test.out");
*/   
    int N;
    int ans = 0;   
    cin >> N;

    for (int i = 1; i <= N; ++i) {
        ll x1, y1, x2, y2, x3, y3;
        ll a, b, c;

        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        
        a = getd(x1,y1,x2,y2);
        b = getd(x2,y2,x3,y3);
        c = getd(x1,y1,x3,y3);

        swaping(a,b,c);
        
        if (a + b == c) {
            ans += 1;
        }
    }

    cout << ans;
    return 0;
}

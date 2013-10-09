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
    int a, b, c, d, in, e;
    cin >> a >> b >> c >> d;
    
    e = __gcd(a,b);
    a /= e; b /= e;
    e = __gcd(c,d);
    c /= e; d /= e;
    
    pair <int, int> p1, p2;
    p1 = mp(a,b);
    p2 = mp(c,d);

    if (p1 > p2) {
        pair <int, int> aux = p2;
        p2 = p1;
        p1 = aux;
    }

    a = p1.f; b = p1.s;
    c = p2.f; d = p2.s;

    in = max(min(c/a, d/b),1);
    a *= in; b *= in;
    
    
    cerr << a << " " << b << " " << c << " " << d ; 
    if (a == c && b == d) {
        cout << 1/1;
        return 0;
    }
    if (a == c) {
        cout << d << "/" << 1;
        return 0;
    }
    
    if (b == d) {
        cout << 1 << "/" << c;
        return 0;
    }
    while(c < a || d < b) {
        c = 2 * c;
        d = 2 * d;
    }

    cout << d/b/__gcd(d / b,c / a) << "/" << c/a/__gcd(d / b,c / a) ;

    return 0;
}

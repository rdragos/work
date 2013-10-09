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

#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long

const int MAXN = 1000;
using namespace std;

double a, b, c, d, p1, p2;

int main() {
/*
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
*/
    cin >> a >> b >> c >> d;
    double p1 = a / b;
    double p2 = c / d;
    
    double res = 0;
    double currprob = 1;

    for (int i = 1; i <= 10000; ++i) {
        res += currprob * p1;
        currprob *= (1 - p1) * (1 - p2);
    }
   
    printf("%.7lf\n", res);  
    return 0;
}

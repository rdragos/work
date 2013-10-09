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

using namespace std;

const int MAXN = 10000000;
int main() {
/*
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
*/    
    int N;
    cin >> N;
    for (int i = MAXN - N; i < MAXN; ++i)
        cout << i << " ";

    return 0;
}

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
    ifstream cin("test.in");
    ofstream cout("test.out");
    
    int N; cin >> N;
    long long s = 0;

    for (int i = 1; i <= N; ++i) {
        int x;
        cin >> x;
        if (x > 1) {
            s = s + (x-1) % 2;
        }
        s %= 2;
    }
//    cerr << s <<"\n";
    if (!(s & 1)) 
        cout << "Constantine";
    else cout << "Mike";
    return 0;
}

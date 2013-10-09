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

//    ifstream cin("test.in");
//    ofstream cout("test.out");
    int n; cin >> n;
    string S; cin >> S;
    
    int ans = 0;
    char last = S[0];

    for (int i = 1; i < n; ++i) {
        if (S[i] == last) {
            ans += 1;
        } else {
            last = S[i];
        }
    }
    cout << ans << "\n";
    return 0;
}

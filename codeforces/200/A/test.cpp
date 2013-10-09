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

    int N; cin >> N;
    int ans = 1;

    string curr;
    cin >> curr;
    
    for (int i = 2; i <= N; ++i) {
        
        string S;
        cin >> S;
        if (S[0] == curr[1]) {
            ans += 1;
            curr = S;
        }

    }

    cout << ans << "\n";
    return 0;
}

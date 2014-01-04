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
    ifstream cin("pufu.in");
    ofstream cout("pufu.out");
    
    int T; cin >> T;
    string V[3] = {"ciocolata", "cascaval", "sare"};

    while(T--) {
        int N; cin >> N;
        
        map <string, int> M;

        for (int i = 0; i < N; ++i) {
            string S; cin >> S;
            M[S] += 1;
        }
        for (int i = 0; i < 3; ++i) {
            cout << M[V[i]] << " " ;
        }
        cout << "\n";
    }
        
    return 0;
}

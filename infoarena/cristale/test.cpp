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
    ifstream cin("cristale.in");
    ofstream cout("cristale.out");
    
    char x, y, z;
    cin >> x >> y >> z;
    int T; cin >> T;
    
    while(T--) {
        int N; cin >> N;
        string S;
        cin >> S;

        vector <int> v(3);
        int s_size = S.size();
        
        for (int i = 0; i < s_size; ++i) {
            if (S[i] == x) {
                v[0]++;
            } else if (S[i] == y) {
                v[1]++;
            } else if (S[i] == z) {
                v[2]++;
            }
        }
        if (v[0] == s_size || v[1] == s_size || v[2] == s_size) {
            cout << s_size << "\n";
            continue;
        }
        if (v[0] & v[1] &  v[2] & 1) {
            cout << 2 << "\n";
            continue;
        } 
        if ( ((v[0] | v[1] | v[2]) & 1) == 0) {
            cout << 2 << "\n";
            continue;
        } cout << 1 << "\n";
    }   
    return 0;
}

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
#include <bitset>

#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;


vector <int> make_prefix(string &S) {
    vector <int> pi(S.size(), 0);
    for (size_t i = 2, q = 0; i < S.size(); ++i) {
        while(q && S[q + 1] != S[i]) {
            q = pi[q];
        }
        if (S[q + 1] == S[i]) {
            q++;
        }
        pi[i] = q;
    }
    return pi;
}
int main() {
    ifstream cin("carte.in");
    ofstream cout("carte.out");
    
    int T; cin >> T;
    while(T--) {
        string A; cin >> A;
        A = " " + A;

        int N; cin >> N;
        int L = A.size();
        vector <string> v(N); 
        bitset <3001> positions[3001];
        for (int i = 0; i < N; ++i) {
            string tmp; 
            cin >> tmp;
            tmp = " " + tmp;
            v[i] = tmp;
        }  
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());  

        vector <int> D(A.size(), 1 << 25);
            
        D[0] = 0;
        for (size_t i = 0; i < v.size(); ++i) {
            vector <int> pi = make_prefix(v[i]);
            int q = 0;
            for (size_t k = 1; k < A.size(); ++k) {

                while(q && A[k] != v[i][q + 1]) {
                    q = pi[q];
                }
                if (v[i][q + 1] == A[k]) {
                    ++q;
                }
                if (q == v[i].size() - 1) {
                    positions[k][k - q] = 1;
                    q = pi[q];
                }
            }
        }

        for (int k = 1; k < A.size(); ++k) {
            D[k] = min(D[k], D[k - 1] + 1);
            for (int j = 0; j < k; ++j) {
                if (positions[k][j]) {
                    D[k] = min(D[k], D[j]);
                }
            }
        }
        cout << D[A.size() - 1] << "\n";

    }
    return 0;
}

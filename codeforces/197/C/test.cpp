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
#include <cassert>
#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

const int MAXM = 1005;
using namespace std;


vector <int> ans;
int d[MAXM][15][15];
pair <int, int> c[MAXM][15][15];

int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/   
    string S;

    cin >> S;
    vector <int> v;
    int M;
    for (int i = 0; i < 10; ++i) {
        if (S[i] == '1') {
            v.pb(i+1);
        }
    }
    cin >> M;

    for (int j = 0; j < v.size(); ++j)
        d[1][v[j]][v[j]] = 1;
    
    for (int t = 2; t <= M; ++t) {

        for (vector <int> :: iterator it1 = v.begin(); it1 != v.end(); ++it1) {
            for (int dif = 1; dif < 10; ++dif) {
                if (*it1 <= dif)
                    continue;

                for (vector <int> :: iterator it2 = v.begin(); it2 != v.end(); ++it2) {
                    if (*it1 == *it2)
                        continue;

                    if (d[ (t-1) ][dif][*it2]) {
                        d[t][*it1 - dif][*it1] = 1;
                        c[t][*it1 - dif][*it1] = make_pair(dif, *it2);
                    }
                }
            }
        }
    }
    
    int difv,kv, ok = 0,kn;
    for (int dif = 1; dif <= 10; ++dif) {
        for (vector <int> :: iterator it = v.begin(); it != v.end(); ++it) {
            if (d[M][dif][*it]) {
                ok = 1;
                difv = dif;
                kv = *it;
            }
        }
    }
    
    if (!ok) {
        cout << "NO\n";
    }
    
    else {
        cout << "YES\n";
        int difn, t;
        t = M;
        
        while(t >= 1) {
            ans.push_back(kv); 
            kn = c[t][difv][kv].second;
            difn = c[t][difv][kv].first;
            kv = kn;
            difv = difn;
            t -= 1;
        }
        reverse(ans.begin(), ans.end());
        for (vector <int> :: iterator it = ans.begin(); it != ans.end(); ++it) {
            cout << *it << " " ;
        }   
    }
    return 0;
}

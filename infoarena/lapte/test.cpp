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

int N;
int L;
const int MAXN = 105;
int selA[MAXN], selB[MAXN];
inline bool cmp(const pair <int, pair <int, int> > &a, const pair <int, pair <int, int> > &b) {
    return a.first * b.second.first == b.first * a.second.first ? a.first < b.first : a.first * b.second.first < b.first * a.second.first;
}
inline int check(int ok, const vector <pair <int, pair <int, int> > > &P, int T) {
    int SA1 = 0, SB1 = 0;
 
    vector <int> lA1(N);
    vector <int> lB1(N);
    
    for (int i = 0; i < N; ++i) {
        lA1[i] = T / P[i].first;
        lB1[i] = (T - lA1[i] * P[i].first) / P[i].second.first;        
    }
    
    for (int i = 0; i < N; ++i) {

        SA1 += lA1[i]; 
        SB1 += lB1[i];

        if (SA1 >= L) {
            int tB = ((SA1 - L) * P[i].first) / P[i].second.first;
            SB1 += tB;

            for (int j = i + 1; j < N; ++j) {
                int t = T / P[j].second.first;
                selB[P[j].second.second] = t; 
                SB1 += t;    
            }
            if(ok == 1) {
                
                for (int j = 0; j < i; ++j) {
                    selA[P[j].second.second] = lA1[j];
                    selB[P[j].second.second] = lB1[j];
                }
                selB[P[i].second.second] = tB + lB1[i];
                selA[P[i].second.second] = (T - tB * P[i].second.first) / P[i].first;
                
                for (int j = 0; j < N; ++j) {
                    cout << selA[j] << " " << selB[j] << "\n";
                }    
            }
            
            if (SB1 >= L) {
                return 1;
            }
            break;         
        }
    }

    return 0;
}
int main() {
    
    freopen("lapte.in", "r", stdin);
    freopen("lapte.out", "w", stdout);

    cin >> N;
    cin >> L;
    
    vector <pair <int, pair <int, int> > > P(N);


    for (int i = 0; i < N; ++i) {
        cin >> P[i].first >> P[i].s.f;
        P[i].s.s = i;

    }
    sort(P.begin(), P.end(), cmp);
 
    int logN = 1;
    int ans = N * 100;

    for (; (1 << logN) <= N * 100; ++logN);
    
     
    for (int pw2 = (1 << logN); pw2 > 0; pw2 >>= 1) {
        
        if (ans - pw2 > 0 && check(0, P,ans - pw2) == 1) {
            ans -= pw2;
        }
    }
    cout << ans << "\n";
    check(1, P, ans);
    return 0;
}

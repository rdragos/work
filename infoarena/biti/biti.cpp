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

const int MAXN = 524289;
using namespace std;
int N;
vector <int> G[MAXN]; 
vector <int> ans;


string toStr(int a) {
    string S = "";
    for (int i = N - 1; i >= 0; --i)
        if (((a & (1 << i)) != 0)) {
            S += "1";
        } else {
            S += "0";
        }
    return S;
}
inline bool cmp(const int &a, const int &b) {
    // returns true if a > b
    for (int i = 0; i < N ; ++i) {
        if ( (a & (1 << i)) == (b & (1 << i))) {
            continue;
        } else {
            return (a & (1 << i)) != 0;
        }
    }
    return 0;
}

int main() {

    ifstream cin("biti.in");
    ofstream cout("biti.out");
    
    cin >> N;
    N -= 1;
    
    if (N == 0) {
        cout << 2 << "\n";
        cout << "01\n";
        return 0;
    }
    /*
    else if (N == 1) {
        cout << "6\n";
        cout << "001011";
        return 0;
    }*/
    for (int i = 0; i < (1 << N); ++i) {
        int v0, v1; 

        v1 = (i >> 1) |  (1 << (N-1));
        v0 = (i >> 1);
        
//        cout << toStr(i) << " " << toStr(v0) << " " << toStr(v1) << "\n";
        G[i].reserve(2); 
        G[i].push_back(v0);
        G[i].push_back(v1);
    }
    
    stack <int> S;
    S.push(G[0][0]); 
    
    while(!S.empty()) {
        int node = S.top(); 
        
        if (G[node].size() > 0) {
            for (vector <int> :: iterator it = G[node].begin(); it != G[node].end(); ++it) {
                S.push(*it);
                G[node].erase(it);
                break;    
            }
        } else {
            ans.push_back(node);
            S.pop();
        }

    }
    string rez = "";
    for (int j = 0; j < ans.size(); ++j) {
        if (ans[j] & (1 << (N-1))) {
            rez += "1";
        } else {
            rez += "0";
        }
        //cout << "\n";
    }
    for (int i = 0; i < N  - 1; ++i)
        rez += "0"; 
    cout << rez.length() << "\n";
    reverse(rez.begin(), rez.end());
    cout << rez ;
    return 0;
}

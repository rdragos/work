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


const int MAXN = 100005;
const int DIM2 = 8192;
using namespace std;


vector <int> divisors[MAXN];
int A[MAXN];

inline bool check(int K) {
    return divisors[K].size() == 0;
}

char vec[DIM2];
int poz;
void cit(int &x)   
{   
  x=0;   
  while(vec[poz]<'0' || vec[poz]>'9')   
       if(++poz==DIM2) fread(vec,1,DIM2,stdin),poz=0;   
   
    while(vec[poz]>='0' && vec[poz]<='9')   
    {   
        x=x*10+vec[poz]-'0';   
        if(++poz==DIM2) fread(vec, 1, DIM2, stdin),poz=0;   
    }  
}   
inline int lower_search(int K, int X) {
    
    int i = divisors[K].size();
    for (int lg = 1 << 18; lg > 0; lg >>= 1) {
        if (i - lg >= 0 && divisors[K][i - lg] >= X) {
            i -= lg;
        }
    } 
    return i;
}
inline int upper_search(int K, int Y) {
    int i = 0;
    int n = divisors[K].size();
    
    for (int lg = 1 << 18; lg > 0; lg >>= 1) {
        if (i + lg < n && divisors[K][i + lg] <= Y) {
            i += lg;
        }
    } 
    return i;
}
int main() {
//    ifstream cin("test.in");
/*
    ofstream cout("test.out");
    freopen("test.in", "r", stdin);
*/
    int N, Q;
    
    cit(N); cit(Q);
    
    for (int i = 1; i <= N; ++i) {
        cit(A[i]);
        for (int k = 1; k * k <= A[i]; ++k) {
            if (A[i] % k == 0) {
                divisors[k].push_back(i);
                if (k * k != A[i]) {
                    divisors[A[i] / k].push_back(i);
                }
            }
        }
    }
     
    for (int i = 1; i < MAXN; ++i) {
        if (divisors[i].size() == 0)
            continue;
        vector <int>(divisors[i]).swap(divisors[i]);
    }
    
    for (int i = 1; i <= Q; ++i) {
        int x, y, k, X, Y;
        cit(x); cit(y); cit(k);
        
        if (check(k)) {
            cout << 0 << "\n";
            continue;
        }
        if (divisors[k][0] > y || divisors[k][divisors[k].size() - 1] < x) {
            cout << 0 << "\n";
            continue;
        }
        X = lower_search(k,x);
        Y = upper_search(k,y);
        
        
        cout << Y - X + 1 << "\n";
    }

    
    return 0;
}

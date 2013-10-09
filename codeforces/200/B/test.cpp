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

string NO = "Impossible";

int A[10] , ord[10];
int B[10][10];
inline bool cmp(const int&a, const int&b) {
    return A[a] > A[b];
}

int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    cin >> A[0] >> A[1] >> A[2];
    for (int i = 0; i < 3; ++i)
        ord[i] = i;
    sort(ord, ord + 3, cmp);
    
    if (A[ord[0]] > A[ord[1]] + A[ord[2]]) {
        cout << NO << "\n";
        return 0;
    } 
    int ok = 0;
    for (int i = 0; i <= A[ord[2]]; ++i) {
        int c1 = A[ord[1]] - i;
        int c2 = A[ord[2]] - i;
        //ord[2] sharing with ord[1] i bonds
        
        if(c1 + c2 == A[ord[0]]) {
            B[ord[1]][ord[2]] = i;
            B[ord[0]][ord[1]] = c1;
            B[ord[2]][ord[0]] = c2;
            ok = 1;
            break;
        }
    }
    if (ok == 0) {
        cout << NO << "\n";
        return 0;
    }
    cout << max(B[0][1], B[1][0]) << " " << max(B[1][2], B[2][1]) << " " << max(B[2][0], B[0][2]) ;
    return 0;
}

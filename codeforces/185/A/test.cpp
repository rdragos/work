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

#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ll long long

const int MAXN = 200;

using namespace std;

int N;
char A[MAXN];

int main() {
//   freopen("test.in", "r", stdin);
//   freopen("test.out", "w", stdout);
    
    scanf("%d\n", &N);

    string strl, strm, strd;

    strl = "Freda's";
    strm = "Rainbow's";
    strd = "OMG>.< I don't know!";

    for (int i = 1; i <= N; ++i) {
        memset(A, '\0', sizeof(A));

        gets(A);
        int n = strlen(A);
        
        int okm = 0;
        int okl = 0;
        
        if (n >= 5)
            okm |= (A[0] == 'm' && A[1] == 'i' && A[2] == 'a' && A[3] == 'o' && A[4] == '.');
        if (n >= 5)
            okl |= (A[n - 1] == '.' && A[n - 2] == 'a' && A[n - 3] == 'l' && A[n - 4] == 'a' && A[n - 5] == 'l');
        
//        cerr << okm << " " << okl << "\n";
        
        if (okm && okl) {
            cout << strd << "\n";
            continue;
        }
        if (okm) {
            cout << strm << "\n";
            continue;
        }
        if (okl) {
            cout << strl << "\n";
            continue;
        }
        cout << strd << "\n";
    }

    return 0;
}

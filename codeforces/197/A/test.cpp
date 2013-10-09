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

/*
ifstream fin("test.in");
ofstream fout("test.out");
*/
int cnt[10];

int main() {
    
    string S;

    cin >> S;

    int rem = 0;
    for (int i = 0; i < S.length(); ++i) 
        if (S[i] >= '1' && S[i] <= '3') {
            cnt[ (S[i] - '0') ] += 1;
            rem += 1;
        }

    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= cnt[i]; ++j) {
            if (rem == 1) {
                cout << i ;
                rem -= 1;
                break;
            }
            else {
                cout << i << '+';
                rem -= 1;
            }
        }
    }

    return 0;
}

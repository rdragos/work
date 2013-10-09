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
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    int N, T;
    string S;

    cin >> N >> T;

    cin >> S;
    

    for (int i = 1; i <= T; ++i) {

        string S2 = S;

        for (int i = 1; i < N; ++i)
            if (S[i] == 'G' && S[i - 1] == 'B')
               swap(S2[i], S2[i - 1]);
        S = S2;
    }
    cout << S << "\n"; 
    return 0;
}

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
    ifstream cin("secv6.in");
    ofstream cout("secv6.out");
    
    int N; cin >> N;
    vector <int> x(min(8192, N));

    for (int i = 0; i < min(N, 8192); ++i) {
        cin >> x[i];
    }
    stack <long long> S;
    
    long long answer = 0;
    for (int i = 0; i < N; ++i) {
        long long a = 1LL * i + (1LL * x[i / 8192] ^ x[i % 8192]);

        while(!S.empty() && a > S.top()) {
            S.pop();
            answer += 1;
        }
        if(!S.empty()) {
            answer += 1;
        }
        while(!S.empty() && a == S.top()) {
            S.pop();
        }
        S.push(a);
    }
    cout << answer << "\n";   
    return 0;
}

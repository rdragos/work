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

stack <char> St;
int main() {
/*
    ifstream cin("test.in");
    ofstream cout("test.out");
*/    
    
    string S; cin >> S;
    int N; N = S.size();

    if (N % 2) {
        cout << "No\n";
        return 0;
    }
    
    for (int i = 0; i < N; ++i) {
        if (St.empty()) {
            St.push(S[i]);
        }

        else if (St.top() == S[i]) {
            St.pop();
        }
        else {
            St.push(S[i]);
        }
    }
    if (St.size() > 0) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    return 0;
}

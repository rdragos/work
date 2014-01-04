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
    ifstream cin("permut.in");
    ofstream cout("permut.out");

    int N; cin >> N;
    vector <int> A(N), B(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> B[i];
    }

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    long long answer = 0;
    for (int i = 0; i < N; ++i) {
        answer += 1LL * A[i] * B[i];
    }
    cout << answer << "\n";
    return 0;
}

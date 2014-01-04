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
    ifstream cin("skyline.in");
    ofstream cout("skyline.out");
    
    int N; cin >> N;
    vector <pair <long long, int> > v(N + 1);
    vector <int> right(N + 1), left(N + 1);

    for (int i = 1; i <= N; ++i) {
        cin >> v[i].first >> v[i].second;
    }

    stack <long long> S; 
    
    left[1] = 1;
    for (int i = 1; i <= N; ++i) {
        while(!S.empty() && v[i].first <= v[S.top()].first) {
            S.pop();
        }
        if (S.empty()) {
            left[i] = 1;
        } else {
            left[i] = S.top() + 1;
        }
        S.push(i);
    }

    while(!S.empty()) {
        S.pop();
    }
    right[N] = N;
    for (int i = N - 1; i >= 1; --i) {
        while(!S.empty() && v[i].first <= v[S.top()].first) {
            S.pop();
        }
        if (S.empty()) {
            right[i] = N;
        } else {
            right[i] = S.top() - 1;
        } 
        S.push(i);
    }

    vector <long long> sum(N + 1);
    for (int i = 1; i <= N; ++i) {
        sum[i] = sum[i - 1] + v[i].second;
    }
    long long answer = 0;
    for (int i = 1; i <= N; ++i) {
        answer = max(answer, 1LL * v[i].first * (sum[right[i]] - sum[left[i] - 1]));
    }
    cout << answer << "\n";
    return 0;
}

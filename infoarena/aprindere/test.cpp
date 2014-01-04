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
    ifstream cin("aprindere.in");
    ofstream cout("aprindere.out");
    
    int N, M;
    cin >> N >> M;

    vector <int> v(N);
    vector <int> t(N);
    vector <vector <int> > action(N, vector <int>());

    for (int i = 0; i < N; ++i) {
        cin >> v[i];
    }

    for (int i = 0; i < M; ++i) {
        int button; cin >> button ; //push the button
        cin >> t[button];
        int nr; cin >> nr;
        for (int j = 0; j < nr; ++j) {
            int x; cin >> x;
            action[button].push_back(x);
        }
    }
    
    int answer = 0;

    for (int i = 0; i < N; ++i) {
        if (v[i] == 0) {
            for (auto &it: action[i]) {
                v[it] ^= 1;
            }
            answer += t[i];
        }
        v[i] = 1;
    }
    cout << answer << "\n";
    return 0;
}

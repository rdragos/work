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


long long solve(vector <int> &v, int k, int max_size) {
    vector <int> frequence(max_size + 1, 0);
    
    int distinct = 0, left = 0;
    long long answer = 0;
    

    for (int i = 0; i < v.size(); ++i) {
        if (frequence[v[i]] == 0) {
            ++distinct;
        }
        frequence[v[i]] += 1;
        while(left <= i && distinct > k) {
            frequence[v[left]] -= 1;
            if (frequence[v[left]] == 0) {
                distinct -= 1;
            }
            ++left;
        }
        if (distinct <= k) {
            answer += (i - left + 1);
        }

    }
    return answer;
}
int main() {
    ifstream cin("secv5.in");
    ofstream cout("secv5.out");
    
    int N, L, U;
    cin >> N >> L >> U;
    vector <pair <long long, int> > v(N);
    vector <int> ord(N);
    for (int i = 0; i < N; ++i) {
        cin >> v[i].first;
        v[i].second = i; 
    }
    sort(v.begin(), v.end());
    
    int distinct = 0;
    for (int i = 1; i < N; ++i) {
        if (v[i].first == v[i - 1].first) {
            ord[v[i].second] = distinct;
        } else {
            ord[v[i].second] = ++distinct;
        }
    }
    cout << solve(ord, U, distinct) - solve(ord, L - 1, distinct) << "\n";
    return 0;
}

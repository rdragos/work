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
#include <unordered_map>

#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

const int MAXN = 1000001;
const int DIM = 8192;

using namespace std;

unordered_map <int, int> H;
int desired_sum;
int visited[MAXN];
vector <int> G[MAXN];
vector <int> value(MAXN);

long long answer = 0;
char vec[DIM];
int pz; 
inline void cit(int& x) {
    x = 0;
    while (vec[pz] < '0' || vec[pz] > '9') {
        if (++pz == DIM) {
            fread(vec, 1, DIM, stdin);
            pz = 0;
        }
    }
    while(vec[pz] >= '0' && vec[pz] <= '9') {
        x = x * 10 + vec[pz] - '0';
        if (++pz == DIM) {
            fread(vec, 1, DIM, stdin);
            pz = 0;
        }
    }
}
void DF(int node, int sum) {
    
    visited[node] = 1;
    H[sum] += 1;
    unordered_map <int, int> :: iterator it = H.find(sum - desired_sum);
    if (it != H.end()) {
        answer += it -> second;
    }
    for (auto &it : G[node]) {
        if (visited[it]) {
            continue;
        }
        DF(it, sum + value[it]);
    }
    H[sum] -= 1;
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int N; 
    cit(N); 
    cit(desired_sum);
    
    for (int i = 0; i < N; ++i) {
        int father; 
        cit(father); cit(value[i]);
        cout << father << " " << value[i] << "\n";
        father -= 1;
        
        if (father == -1) {
            continue;
        }
        G[father].push_back(i);
    }
    H[0] += 1;
    DF(0, value[0]);
    cout << answer << "\n";
    return 0;
}

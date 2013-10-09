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

const int MAXN = 100005;

using namespace std;


int W[MAXN], C[MAXN];
int ord[MAXN];
double P[MAXN];
int N, G;

void exponential_solve() {
    
    int ans = 0, max_cost = 0;

    for (int mask = 1; mask < (1 << N);  mask += 1) {
        int c_c = 0, c_w = 0;
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                c_w += W[i];
                c_c += C[i];
            }
        }
        if (c_w <= G && c_c > max_cost) {
            max_cost = c_c;
            ans = mask;
        }
    }
    for (int i = 0; i < N; ++i) {
        if (ans & (1 << i)) {
            cout << i << " " ;
        }
    }
    cout << "\nCostul maxim este " << max_cost << "\n";

}

void pd_solve() {
    
    int *D = new int[MAXN + 1]; 
    int *T = new int[MAXN + 1];
    D[0] = 0;
    int max_cost = 0, fat = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = G - W[i]; j >= 0; --j) {
            if (D[j + W[i]] < D[j] + C[i]) {
                D[j + W[i]] = D[j] + C[i];
                T[j + W[i]] = i;
            }
        }
    }
    
    for (int j = G; j >= 0; --j) {
        if (D[j] > max_cost) {
            max_cost = D[j];
            fat = j;
        }
        
    }
    while(fat != 0) {
        cout << fat << " ";
        fat = fat - T[fat];
    }
    cout << "\nCostul maxim este " << max_cost << "\n";
    delete[] D;
    delete[] T;
}

struct cmp
{
    bool operator () (const int &a, const int &b) {
        return P[a] < P[b];
    }
};
void heap_solve() {

    
    priority_queue <int, vector <double>, cmp> pq;

    for (int i = 0; i < N; ++i) {
        P[i] = W[i]/ (1.0 * C[i]);
    }
    for (int i = 0; i < N; ++i)
        pq.push(i);

    int c_w = 0;
    int c_c = 0;

    while(c_w <= G && !pq.empty()) {
        int t = pq.top();
        c_w += W[t];
        if (c_w > G) {
            break;
        }
        c_c += C[t];
        cout << t << " ";
        pq.pop();
    }
    cout << "\nCostul maxim este\n" << c_c;
}
int main() {
    ifstream cin("test.in");
    ofstream cout("test.out");
    

    cin >> N >> G;
    
    for (int i = 0; i < N; ++i)
        cin >> W[i] >> C[i];

    if (N <= 22) {
        exponential_solve();
    }
    else if (G < MAXN) {
        pd_solve();
    }
    else {
        heap_solve();
    }

    return 0;
}

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

const int MAXN = 200005;
const int MAXT = 20005;

using namespace std;

int table[MAXN], required_table[MAXT], cnt_ret[MAXT];

int main() {
    ifstream cin("panouri.in");
    ofstream cout("panouri.out");

    int N; int T; cin >> N >> T;
    
    for (int i = 1; i <= N; ++i) {
        cin >> table[i];
    }

    for (int i = 0; i < T; ++i) {
        int val; cin >> val ; 
        required_table[val] = 1;
    }
    
    int n_temp = 0;
    int solution = 1 << 30;  
    

    int left = N ;
    for (int i = 1; i <= N; ++i) {
        if (required_table[table[i]]) {
            
            if (cnt_ret[table[i]] == 0) {
                //insert a value not meeted
                n_temp += 1;
            } 
            left = min(left, i);
            cnt_ret[table[i]] += 1;
            
            if(n_temp < T) {
                continue;
            }
            
            while(cnt_ret[table[left]] > 1 || (!required_table[table[left]])){
                if(required_table[table[left]]) {
                    cnt_ret[table[left]] -= 1;
                }
                left += 1;  
            }
            
            solution = min(solution, i - left);
        }
    }
    if (solution == 1 << 30) {
        cout << -1 << "\n";
    } else {
        cout << solution << "\n";
    }
    return 0;
}

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
#include <cassert>
#include <cmath>
#include <bitset>

#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;

const int MAXN = 8192;
char vec[MAXN + 1];
int pz;
inline void cit(int &x) {
    x = 0;
    while(vec[pz] < '0' || vec[pz] > '9') {
        if (++pz == MAXN) {
            fread(vec, 1, MAXN, stdin);
            pz = 0;
        }
    }

    while(vec[pz] >= '0' && vec[pz] <= '9') {
        x = x * 10 + vec[pz] - '0';
        if (++pz == MAXN) {
            fread(vec, 1, MAXN, stdin);
            pz = 0;
        }
    }
}

int main() {
    
    freopen("missnr.in", "r", stdin);
    ofstream cout("missnr.out");

    int N;cit(N);
    
    int szBucket = sqrt(N);
    vector <int> bucket(szBucket + 1, 0);

    for (int i = 1; i < N - 1; ++i) {
        int x; cit(x);
        bucket[x / szBucket] += 1;    
        //cerr << x << " " << x / szBucket << "\n";
    }
    vector <int> candidates; 
    for (int i = 0; i <= szBucket; ++i) {
        int q = min(N, (i + 1) * szBucket - 1 ) - max(1, i * szBucket) + 1; 
        
        //cerr << bucket[i] << " " << i * szBucket << " " << (i + 1) * szBucket - 1 <<"\n";    
        if (bucket[i] != q) {
            candidates.push_back(i);
        }
    }
    
    int left1, right1, left2, right2;
    left1 = left2 = 0;
    right1 = right2 = -2;

    left1 = max(1, candidates[0] * szBucket), right1 = min(N, (candidates[0] + 1) * szBucket - 1);
    if (candidates.size() > 1) {
        left2 = max(1, candidates[1] * szBucket), right2 = min(N, (candidates[1] + 1) * szBucket - 1);
    }
    bitset<1600> freq1, freq2;
    
    fclose(stdin); 
    freopen("missnr.in", "r", stdin);
    memset(vec, '\0', sizeof(vec));
    pz = MAXN-1;
    
    cit(N);
    
    for (int i = 0; i < N - 2; ++i) {
        int x; cit(x);
        if (x >= left1 && x <= right1) {
            freq1[x - left1] = 1;
            continue;
        }
        if (x >= left2 && x <= right2) {
            freq2[x - left2] = 1;
        } 
    }
    
    for (int i = 0; i < right1 - left1 + 1; ++i) {
        if (freq1[i] == 0) {
            cout << i + left1 << " " ;
        }
    }

    for (int i = 0; i < right2 - left2 + 1; ++i) {
        if (freq2[i] == 0) {
            cout << i + left2 << " " ;
        }
    }

    return 0;
}

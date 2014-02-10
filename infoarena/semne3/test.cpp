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


void swaping(vector <int> &sol, int pozx, int pozy) {
    vector <int> aux(pozy - pozx + 1, 0);
    /*
    cerr << pozx << " "<< pozy << "\n";
    for (int j = pozx; j <= pozy; ++j) {
        cerr << sol[j] << " ";
    }
    cerr << "\n";
    */
    for (int j = pozx; j <= pozy; ++j) {
        aux[j - pozx] = sol[j];
    }
    for (int j = pozy; j >= pozx; --j) {
        sol[j] = aux[pozy - j];
    }
    /*
    for (int j = pozx; j <= pozy; ++j) {
        cerr << sol[j] << " " ;
    }
    cerr << "\n";
    */
}
int main() {
    ifstream cin("semne3.in");
    ofstream cout("semne3.out");
    
    int N; cin >> N;
    
    string buff;
    cin >> buff;

    vector <int> sol(N); 
    for (int i = 0; i < N; ++i) {
        sol[i] = i + 1;
    }

    int pozx = 0;
    int ant = 0;

    for (int i = 0; i < N - 1; ++i) {
        if (buff[i] == '>') {
            if (ant == 0) {
                pozx = i;
                ant = 1;
            }
        } else {
            if (ant > 0) {
                swaping(sol, pozx, i);
            }
            ant = 0;
        }
    }           
    if (ant) {
        swaping(sol, pozx, N - 1);
    }
    for (int i = 0; i < N; ++i) {
        cout << sol[i] << " " ;
    }

    return 0;
}

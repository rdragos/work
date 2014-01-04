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

#define DIM 10000
char buff[DIM];
int poz=0;
 
inline void cit(int &numar)
{
     numar = 0;
     char semn='+';     
     while (buff[poz] < '0' || buff[poz] > '9')
     {     
          semn = buff[poz];
          if (++poz == DIM) 
               fread(buff,1,DIM,stdin),poz=0;
     }          
     while ('0'<=buff[poz] && buff[poz]<='9')
     {
          numar = numar*10 + buff[poz] - '0';
          if (++poz == DIM) 
               fread(buff,1,DIM,stdin),poz=0;               
     }     
     if (semn == '-')
          numar = -numar;
}

int main() {
    freopen("magicmatrix.in", "r", stdin);
    freopen("magicmatrix.out", "w", stdout);

    int T; cit(T);
    srand(time(NULL));
    for(; T--; ) {
        int N; cit(N);
        vector <vector <int> > matrix(N, vector <int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cit(matrix[i][j]);
            }
        }
        
        vector <int> perm(N);
        long long sum = 0;

        for (int i = 0; i < N; ++i) {
            perm[i] = i; 
            sum += matrix[i][i];
        }
        
        string answer = "YES";

        for (int t = 0; t < 5e3; ++t) {
            random_shuffle(perm.begin(), perm.end());
            long long t_sum = 0;

            for (int i = 0; i < N; ++i) {
                t_sum += matrix[i][perm[i]];
            }
            if (t_sum != sum) {
                answer = "NO";
                break;
            }
        }
        cout << answer << "\n";
    }
    return 0;
}

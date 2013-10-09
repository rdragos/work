#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <unordered_map>
#define pii pair<int,int>
#define x first
#define y second
#define mp make_pair
#define REP(i,n) for(int i = 0;i < (int)n;i++)
#define i64 long long

using namespace std;
const int DIM2 = 8192;
char vec[DIM2];
int poz;
void cit(short &x)   
{   
  x=0;   
  while(vec[poz]<'0' || vec[poz]>'9')   
       if(++poz==DIM2) fread(vec,1,DIM2,stdin),poz=0;   
   
    while(vec[poz]>='0' && vec[poz]<='9')   
    {   
        x=x*10+vec[poz]-'0';   
        if(++poz==DIM2) fread(vec, 1, DIM2, stdin),poz=0;   
    }  
}   
const string rr[2] = {"NO\n","YES\n"};
const int nmax = 2502;
int n, m;
char A[nmax];
short S[2][nmax][nmax];
int Q;


void readData() {
	cin>>n>>m;
	cin.get();
	
}
inline void SWAP(short &a,short &b) {
	short tmp = a;
	a = b;
	b = tmp;
}

inline short query(short &r1,short &c1,short &r2,short &c2) {
	if(r1 == r2) {
		return c1 > c2 ? S[0][r1][c1] - S[0][r1][c2 - 1] : S[0][r1][c2] - S[0][r1][c1 - 1];
	}
	return r1 > r2 ? S[1][r1][c1] - S[1][r2 - 1][c1]  : S[1][r2][c1] - S[1][r1 - 1][c1];

}

char str[32];
#define isDigit(c) ('0' <= c && c <= '9')

void solve() {
	REP(i,n) {
		cin.getline(A,nmax);
		REP(j,m) {
			bool wall = (A[j] == '#');
			S[0][i + 1][j + 1] = S[0][i + 1][j] + wall;
			S[1][i + 1][j + 1] = S[1][i ][j + 1] + wall;
		}
	}

	cin>>Q;
	cin.get();
	//cout<<Q<<"\n";
	short cc[4];
	for(;Q;Q--) {	
        cit(cc[0]); cit(cc[1]); cit(cc[2]); cit(cc[3]);
        
		if(cc[0] == cc[2]) {
			cout<<rr[query(cc[0],cc[1],cc[2],cc[3]) == 0];
		}
		else
		if(cc[1] == cc[3]) {
			cout<<rr[query(cc[0],cc[1],cc[2],cc[3]) == 0];
		} else {
				if(cc[0] > cc[2]) {
				SWAP(cc[0],cc[2]);
				SWAP(cc[1],cc[3]);
			}
			cout<<rr[  (query(cc[0],cc[1],cc[0],cc[3]) + query(cc[2],cc[3],cc[0],cc[3]) == 0 ) | (query(cc[0],cc[1],cc[2],cc[1]) + query(cc[2],cc[3],cc[2],cc[1]) == 0)  ];
			
		}
	
	}
}
		
int main()
{
	//freopen("test.in","r",stdin); freopen("test.out","w",stdout);//cin.sync_with_stdio(false), cout.sync_with_stdio(false);
	readData();
	solve();
	return 0;
}

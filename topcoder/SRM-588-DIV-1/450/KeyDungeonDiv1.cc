

// {{{ Boilerplate Code <--------------------------------------------------
// vim:filetype=cpp:foldmethod=marker:foldmarker={{{,}}}

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstring>

#define FOR(I,A,B) for(int I = (A); I < (B); ++I)
#define REP(I,N)   FOR(I,0,N)
#define ALL(A)     (A).begin(), (A).end()

using namespace std;

// }}}

class KeyDungeonDiv1
{
    
  public:
    vector <int> doorR, doorG, roomR, roomG, roomW, keys;
    int ans, n;
    char visited[1 << 12][125];

    void dfs(int mask, int X) {
        if (visited[mask][X])
            return ;
        
        visited[mask][X] = 1;

        int r = keys[0] + X;
        int g = keys[1] + keys[2] - X;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                r += roomR[i] - doorR[i];
                g += roomG[i] - doorG[i] + roomW[i];
            }
        }
        
        ans = max(ans, r + g);
    
        for (int i = 0; i < n; ++i) {
            if (! (mask & (1 << i)) ) {
                if (r >= doorR[i] && g >= doorG[i]) {
                    for (int x = 0 ; x <= roomW[i]; ++x) {
                        dfs(mask | (1 << i) , X + x);
                    }
                }
            }
        }
    }

	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys) {
        
        this -> doorR = doorR;
        this -> doorG = doorG;
        this -> roomR = roomR;
        this -> roomG = roomG;
        this -> roomW = roomW;
        this -> keys = keys;
        this -> n = doorR.size();
        this -> ans = 0;

        memset(visited, 0, sizeof(visited));

        for (int i = 0; i <= keys[2] ; ++i) {
            dfs(0, i);
        }

        return ans;
	}
};


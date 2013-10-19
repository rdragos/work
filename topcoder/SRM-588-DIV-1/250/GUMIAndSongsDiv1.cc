
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

#define FOR(I,A,B) for(int I = (A); I < (B); ++I)
#define REP(I,N)   FOR(I,0,N)
#define ALL(A)     (A).begin(), (A).end()

using namespace std;

// }}}

class GUMIAndSongsDiv1
{
public:
	int maxSongs(vector <int> duration, vector <int> tone, int T)
	{   
            
        int n = tone.size();
    
        int ans = 0;

        for (int i = 0; i < n; ++i)
            if (duration[i] <= T) {
                ans = 1;
                break;
            }

        for (int a = 0; a < tone.size(); ++a) {
            for (int b = a + 1; b < tone.size(); ++b) {
                
                int ta = tone[a];
                int tb = tone[b];

                if (ta > tb) {
                    swap(ta, tb);
                }

                int _T = T - tb + ta - (duration[a] + duration[b]);
                
                if (_T < 0) {
                    continue;
                }

                priority_queue <int> pq;

                for (int i = 0; i < n; ++i) {
                    if (i == a || i == b || tone[i] < ta || tone[i] > tb) {
                        continue;
                    }
                    pq.push(-duration[i]);
                }
                
                int tmp_ans = 2;

                while(_T > 0) {
                    if (pq.empty()) {
                        break;
                    }
                    _T -= (-1) * pq.top();
                    pq.pop();
                    if (_T >= 0) {
                        tmp_ans += 1;
                    }
                }

                ans = max(ans, tmp_ans);
            }
        }

		return ans;
	}
};

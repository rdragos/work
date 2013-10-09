
// {{{ Boilerplate Code <--------------------------------------------------
// vim:filetype=cpp:foldmethod=marker:foldmarker={{{,}}}

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
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

class GooseTattarrattatDiv1
{
  private:
      vector <int> graph[30];
      int visited[30];

      void DF(int node, int col) {
            visited[node] = col;
            for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++it) {
                if (visited[*it] == 0)
                    DF(*it, col);
            }
      }

  public:

	int getmin(string S)
	{   
        int n = S.size();
        vector <int> A(n);
        int F[30];
        memset(visited, 0, sizeof(visited));
        memset(F, 0, sizeof(F));
        
        for (int i = 0; i < n; ++i) {
            A[i] = (int)(S[i] - 'a');
            F[A[i]] += 1;
        }

		for (int lf = 0, rt = n - 1; lf <= rt; ++lf, --rt) {
            if (A[lf] != A[rt]) {
                graph[A[lf]].push_back(A[rt]);
                graph[A[rt]].push_back(A[lf]);
            }
        }
        int nrc = 0;

        for (int i = 0; i < 30; ++i) {
            if (!visited[i]) {
                if (graph[i].size() == 0)
                    continue;
                nrc += 1;
                DF(i, nrc);
                
            }
        }
        int ans = 0;
        cout << "this is nrc: " << nrc << "\n";
        for (int i = 1; i <= nrc; ++i) {
            int c_ans = 0, mx = 0;
            for (int j = 0; j < 30; ++j)
                if (visited[j] == i) {
                    c_ans += F[j];
                    mx = max(F[j], mx);
                }
            ans += c_ans - mx;
        }
        return ans;
	}
};


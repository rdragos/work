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
 
const int MAXN = 95;
const int MAXM = 320;
 
using namespace std;

vector <int> G[MAXN];
vector <int> solution[19];
char marked_edges[MAXM];
vector <int> current_nodes;
pair <int, int> edge[MAXM];
int N, M;
vector <int> S;
 
 
void back(int count_nodes, int current_edges) {
     
    if (count_nodes > 18) {
        return ;
    }
    if (current_edges == M) {
        if (solution[count_nodes].empty()) {
            solution[count_nodes] = S;
        }
        return ;
    }
    for (int i = 1; i <= M; ++i)
        if (marked_edges[i] == 0) {
            //use first vertex
            
            char save_edges[MAXM];
            int cnt = 0;
            int node = edge[i].f;
            memcpy(save_edges, marked_edges, sizeof(marked_edges));
            
            for (auto it = G[node].begin(); it != G[node].end(); ++it) {
                cnt += (save_edges[*it]== 0);
                marked_edges[*it] = 1;
            }

            S.push_back(node);
            back(count_nodes + 1, current_edges+ cnt);
            //revert changes
            S.pop_back();
            memcpy(marked_edges, save_edges, sizeof(save_edges));
            //do some push-ups
            node = edge[i].s;
            cnt = 0;
            for (auto it = G[node].begin(); it != G[node].end(); ++it) {
                cnt += (save_edges[*it] == 0);
                marked_edges[*it] = 1;
            }
            
            S.push_back(node);
            back(count_nodes + 1, current_edges + cnt);
            //revert changes
            S.pop_back();
            memcpy(marked_edges, save_edges, sizeof(save_edges));
            return ;
        }
}
int main() {
    ifstream fin("rmvc.in");
    ofstream fout("rmvc.out");
     
    fin >> N >> M;
     
    for (int i = 1; i <= M; ++i) {
        int a, b;
 
        fin >> a >> b;
        edge[i] = make_pair(a,b);
        G[a].push_back(i);
        G[b].push_back(i);
    }
    // take every node and see if you can obtain all the edges - like an xor on nodes
     
     
    back(0, 0);
    for (int i = 1; i < 19; ++i) {
        if (solution[i].size() > 0) {
            fout << solution[i].size() <<"\n";
            for (int j = 0; j < solution[i].size(); ++j) {
                fout << solution[i][j] << " ";
            }
            return 0;
        }
    }
 
 
    return 0;
}

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
#include <omp.h>
#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;


class Graph {
 public:
    Graph(int _N) {
        N = _N;
        viz.assign(N, 0);
        L.assign(N, -1);
        R.assign(N, -1);
        edge_mask.assign(N, 0);
        edges.assign(N, vector<int>());
    }
    Graph(const Graph &other): L(other.L), R(other.R), edge_mask(other.edge_mask) {
        N = other.N;
        viz.assign(N, 0);
        edges.assign(N, vector<int>());
        for (int i = 0; i < N; ++i) {
            edges[i].assign(other.edges[i].size(), 0);
            std::copy(other.edges[i].begin(), other.edges[i].end(), edges[i].begin());
        }
    }
    void addEdge(int x, int y) {
        edges[x].push_back(y);
        edge_mask[y] ^= (1 << x);
    }

    void pop_vertex(int x) {
        int y = edges[x].back();
        edges[x].pop_back();
        edge_mask[y] ^= (1 << x);
    }

    bool pairup(int node) {
        if (viz[node]) {
             return 0;
        }
        viz[node] = 1;
        for (auto vec: edges[node]) {
            if (R[vec] == -1) {
                L[node] = vec;
                R[vec] = node;
                return 1;
            }
        }
        for (auto vec: edges[node]) {
            if (pairup(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return 1;
            }
        }
        return 0;
    }

    int maxMatch(int last_node) {
        int change = 1;
        while(change) {
            change = 0;
            for (int i = 0; i <= last_node; ++i) {
                viz[i] = 0;
            }
            if (L[last_node] == -1) {
                change |= pairup(last_node);
            }
        }
        if (L[last_node] != -1) {
            return 1;
        } else {
            //check intersection
            for (int i = 0; i <= last_node; ++i) {
                if (edge_mask[i] == 0) {
                    return 2;
                }
                int res = (edge_mask[i] & edge_mask[last_node]);
                if (res == edge_mask[i]) {
                    continue;
                }
                if (res == edge_mask[last_node]) {
                    continue;
                }
                return 2;
            }
            return 0;
        }
    }

    void write() {
        vector<vector<int>> assign(N, vector<int>());
        for (int i = 0; i < N; ++i) {
            for (auto vertex: edges[i]) {
                assign[vertex].push_back(i);
            }
        }

        for (int i = 0; i < N; ++i) {
            cout << "set " << i << ": ";
            cout << "{ ";
            if (assign[i].size() > 0) {
                for (int j = 0; j < assign[i].size() - 1; ++j) {
                    cout << assign[i][j] << " " ;
                }
                cout << *assign[i].rbegin();
            }

            cout << " }";
            cout << "\n";
        }
    }
    vector<int> edge_mask;
    vector<int> L, R;
    vector<vector<int>> edges;
    vector<int> viz;
    int N;
};
class Solver{
 public:

     Solver(int _N) {
         N = _N;
         edge_c.assign(1<<N,set<int>());
         mark.assign(1<<N, 0);
         edge_mask.assign(N, 0);
         SOL = 0;
     }
     void gen_canceling_sets() {
        for (int conf1 = 0; conf1 < (1 << N); ++conf1) {
            for (int conf2 = 0; conf2 < (1 << N); ++conf2) {
                int inter = conf1 & conf2;
                if (inter == conf1 || inter == conf2) {
                    edge_c[conf1].insert(conf2);
                    edge_c[conf2].insert(conf1);
                }
            }
        }
        for (int conf1 = 1; conf1 < (1 << N) - 1; ++conf1) {
            candidates.insert(conf1);
        }
     }

     int check_sets_intersect(Graph& G) {
         for (int i = 0; i < N; ++i) {
             for (int j = i + 1; j < N; ++j) {
                 if ( (G.edge_mask[i] & G.edge_mask[j]) == 0) {
                     return 0;
                 }
             }
         }
         vector<int> tmp(G.edge_mask);
         sort(tmp.begin(), tmp.end());
         if (unique_matchings.find(tmp) == unique_matchings.end()) {
             unique_matchings.insert(tmp);
                #pragma omp critical
             {
                 G.write();
                 cerr << "\n";
             }
         }
         return 1;
     }
     void back(int k, Graph G, set<int> select) {
         if (k == N) {
             // do i really care about this?
         //   SOL += check_sets_intersect(G);
            //SOL += 1;
         } else {
             vector <int> vec_select(select.begin(), select.end());
            #pragma omp parallel for firstprivate(select, G)
             for (int i = 0; i < vec_select.size(); ++i) {
                 int conf = vec_select[i];
                 for (int bit = 0; bit < N; ++bit) {
                     if (conf & (1 << bit)) {
                         G.addEdge(k, bit);
                     }
                 }

                 int matching_result = G.maxMatch(k);
                 if (matching_result == 0) {
                     cout << "NO MAX MATCH\n";
                     G.write();
                 }
                 vector<int> to_erase;

                 for (const auto& temp: edge_c[conf]) {
                     auto tmpconf = temp;
                     set<int>::iterator it = select.find(tmpconf);
                     if (it != select.end()) {
                         to_erase.push_back(tmpconf);
                         select.erase(it);
                     }
                 }
                 back(k + 1, G, select);

                 for (auto tmpconf: to_erase) {
                     select.insert(tmpconf);
                 }

                 for (int bit = 0; bit < N; ++bit) {
                     if (conf & (1 << bit)) {
                         G.pop_vertex(k);
                     }
                 }
             }
         }
     }
     void solve() {
         gen_canceling_sets();
         cout << "finished pre_processing\n";

         Graph G(N);
         back(0, G, candidates);
         //Graph B(G);
         //B.write();
         cout << "found " << unique_matchings.size() << " matchings\n";
     }
     vector<set<int>> edge_c;
     vector<int> edge_mask;
     vector<int> mark;
     set<int> candidates;
     set<vector<int>> unique_matchings;
     int N;
     int SOL;

};
int main() {
  ifstream cin("test.in");
  ofstream cout("test.out");

  int N; cin >> N;
  Solver S(N);
  S.solve();
  return 0;
}

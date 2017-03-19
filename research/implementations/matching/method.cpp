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

int kLim = 1000000;
class Solver {
  public:
    
    Solver(int _N) {
        N = _N;
        edge_c.resize(1<<N,set<int>());
        edges_v.assign(N,vector<int>());
        viz.assign(N, 0);
        L.assign(N, 0);
        R.assign(N, 0);
        edge_mask.assign(N,0);
        ret.assign(N+1, vector<int>(1<<N, 0));
        for (int mask = 1; mask < (1 << N); ++mask) {
            candidates.insert(mask);
        }
        cnt = 0;
    }
    void print_bits(int conf) {
        for (int i = 0; i < N; ++i) {
            if (conf & (1 << i)) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
        cout << "\n";
    }
    void add_cancel(int conf, int subset) {
        for (auto v: edge_c[subset]) {
            edge_c[conf].insert(v);
        }
    }
    void gen_canceling_sets() {
        for (int conf = 0; conf < (1 << N); ++conf) {
            edge_c[conf].insert(conf);
            for (int subset = conf; subset > 0; subset = conf & (subset - 1)) {
                add_cancel(conf, conf - subset); 
            }
            /*
            cout << "conf:\n";
            print_bits(conf);
            for (auto v: edge_c[conf]) {
                print_bits(v);
            }
            cout << "*\n";
            */
        }
        cerr << "making..\n";
        // make the graph undirected;
        for (int conf = 0; conf < (1 << N); ++conf) {
            for (auto val: edge_c[conf]) {
                if (edge_c[val].find(conf) == edge_c[val].end()) {
                    edge_c[val].insert(conf);
                }
            }

        }
        cerr << "finished making...";
    }
    void debug_graph() {
        for (int i = 0; i < N; ++i) {
            //cout << i << " -> ";
            //cout << "{";

            vector<int> Ans;
            for (int j = 0; j < N; ++j) {
                if (edge_mask[i] & (1 << j)) {
                    Ans.push_back(j + 1);
                }
            }
            for (int j = 0; j < Ans.size() - 1; ++j) {
                cout << Ans[j] << " ";
            }
            cout << *Ans.rbegin() << "\n";
        }
    }
    void debug_matching() {
        for (int i = 0; i < N; ++i) {
            cout << i << " -> ";
            cout << "{";
            for (int j = 0; j < edges_v[L[i]].size() - 1; ++j) {
                cout << edges_v[L[i]][j] << " ";
            }
            cout << *edges_v[L[i]].rbegin() << "}";
            cout << "\n";
        }
    }
    bool pairup(int node) {
        if (viz[node]) {
             return 0;
        }
        viz[node] = 1;
        for (auto vec: edges_v[node]) {
            if (R[vec] == -1) {
                L[node] = vec;
                R[vec] = node;
                return 1;
            }
        }
        for (auto vec: edges_v[node]) {
            if (pairup(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return 1;
            }
        }
        return 0;
    }

    set<vector<int>> store;
    void check_matching() {
        // check if Q2
        //
        if (store.size() <= kLim) {
            vector<int> V(N);
            for (int i = 0; i < N; ++i) {
                V[i] = edge_mask[i];
            }
            sort(V.begin(), V.end());
            if (store.find(V) != store.end()) {
                return ;
            }
            store.insert(V);
        }
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (!(edge_mask[i] & edge_mask[j])) {
                    return ;
                }
                if ( (edge_mask[i] & edge_mask[j]) == edge_mask[i]) {
                    return ;
                }
                if ( (edge_mask[i] & edge_mask[j]) == edge_mask[j]) {
                    return ;
                }
            }
        }
        for (int i = 0; i < N; ++i) {
            viz[i] = 0;
            L[i] = R[i] = -1;
        }
        int change = 1;
        while(change) {
            change = 0;
            for (int i = 0; i < N; ++i) {
                viz[i] = 0;
            }
            for (int i = 0; i < N; ++i) {
                if (L[i] == -1) {
                    change |= pairup(i);
                }
            }
        }
        for (int i = 0; i < N; ++i) {
            if (L[i] == -1) {
                cout << "NO";
                debug_graph();
                return ;
            }
        }
        cnt += 1;
        //cout << "Matched\n";
        //debug_graph();
        //debug_matching();
    }
    void back(int k, int conf) {
        if (k == N) {
            check_matching();
        } else {
            set<int,greater<int>> tmp = candidates;
            for (auto mask: tmp) {
                //select val and now erase next candidates using edge_c
                vector<int> erased_vals;
                for (auto to_erase: edge_c[mask]) {
                    if (candidates.find(to_erase) != candidates.end()) {
                        erased_vals.push_back(to_erase);
                        candidates.erase(to_erase);
                    }
                }
                for (int bit = 0; bit < N; ++bit) {
                    if (mask & (1 << bit)) {
                        edges_v[bit].push_back(k);
                        edge_mask[bit] ^= (1 << k);
                    }
                }
                back(k + 1, mask);

                for (int bit = 0; bit < N; ++bit) {
                    if (mask & (1 << bit)) {
                        edges_v[bit].pop_back();
                        edge_mask[bit] ^= (1 << k);
                    }
                }
                for (auto val: erased_vals) {
                    candidates.insert(val);
                }
            }
        }
    }
    void solve() {
        gen_canceling_sets();
        cerr << "started to generate sets...";
        back(0, 0);
        cerr << "sets: " << cnt << "\n";
    }
  private:
    vector<set<int>> edge_c;
    vector<vector<int>> edges_v;
    set<int,greater<int>> candidates;
    vector<vector<int>> ret;
    vector<int> viz, L, R;
    vector<int> edge_mask;
    int N;
    int cnt;
};
int main() {
    ifstream cin("test.in");
    ofstream cout("test.out");

    int N; cin >> N;
    Solver S(N);
    S.solve();
}

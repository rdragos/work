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


void DF(int node, 
        vector <vector <int> > &graph,
        vector <int> &distance) {

    for (auto &it : graph[node]) {
        if (distance[it]) {
            continue;
        }
        distance[it] = distance[node] + 1;
        DF(it, graph, distance);
    }
}


int find_maximum_path(vector <vector <int> > &graph, int N) {
    vector <int> distance(N);
    
    distance[0] = 1;
    DF(0, graph, distance);
    
    int path = 0;
    int furthest_node = 0;

    for (int i = 0; i < N; ++i) {
        if (distance[i] > path) {
            path = distance[i];
            furthest_node = i;
        }
    }
    for (int i = 0; i < N; ++i) {
        distance[i] = 0;
    }
    distance[furthest_node] = 1;
    DF(furthest_node, graph, distance);

    for (int i = 0; i < N; ++i) {
        if (distance[i] > path) {
            path = distance[i];
            furthest_node = i;
        }
    }
    return path - 1; 
}
int main() {
    ifstream cin("apdm.in");
    ofstream cout("apdm.out");
    
    srand(time(NULL));

    int N; cin >> N;
    vector <vector <int> > edges(N, vector<int>());
    int M; cin >> M;
    
    vector <pair <int, int> > P(M);
    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        x -= 1; y -= 1;
        edges[x].push_back(y);
        edges[y].push_back(x);
        P[i] = make_pair(x, y);
    }
    
    random_shuffle(P.begin(), P.end());

    int answer = N;

    for (int i = 0; i < N + min(300, M); ++i) {
        queue <int> Q; 
        vector <int> visited(N, 0);
        vector <vector <int> > graph(N, vector <int>());
        
        
        if (i >= N) {
            int x = P[i - N].first;
            int y = P[i - N].second;
            
            graph[x].push_back(y);
            graph[y].push_back(x);
            Q.push(x); Q.push(y);
            visited[x] = visited[y] = 1;
        } else {
            Q.push(i);
            visited[i] = 1;
        }
        
        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for (auto &it : edges[x]) {
                if (!visited[it]) {
                    graph[x].push_back(it);
                    graph[it].push_back(x);
                    Q.push(it);
                    visited[it] = 1;
                }
            }
        }
        //cerr << i << " " << find_maximum_path(graph, N) << "\n";
        answer = min(answer, find_maximum_path(graph, N));
    }
    cout << answer << "\n";
    return 0;
}

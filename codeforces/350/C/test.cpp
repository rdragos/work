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

int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */


  int N; cin >> N;
  vector<int> V(N);
  for (int i = 0; i < N; ++i) {
    cin >> V[i];
  }

  int M; cin >> M;
  vector <int> A(M);
  vector <int> B(M);

  map <int, int> H;

  for (int i = 0; i < M; ++i) {
    cin >> A[i];
  }
  for (int i = 0; i < M; ++i) {
    cin >> B[i];
  }

  for (int i = 0; i < N; ++i) {
    H[V[i]] += 1;
  }

  int max_sat = -1;
  int max_pl = -1;

  int idx = 0;
  for (int i = 0; i < M; ++i) {
    int pl = H[A[i]];
    int sat = H[B[i]];

    if (pl > max_pl) {
      max_pl = pl;
      max_sat = sat;
      idx = i;
    } else if (pl == max_pl) {
      if (sat > max_sat) {
        idx = i;
        max_sat = sat;
      }
    }
  }
  cout << idx + 1 << "\n";
  return 0;
}

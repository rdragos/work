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

  int N, M, P; cin >> N >> M >> P;
  string S; cin >> S;
  S = "$" + S + "$";

  string comm; cin >> comm;


  vector <int> next(N + 2), prev(N + 2), match(N + 2);
  stack <int> st;

  next[0] = 1;
  for (int i = 1; i <= N; ++i) {

    prev[i] = i - 1;
    next[i] = i + 1;

    if (S[i] == '(') {
      st.push(i);
    } else {
      int poz = st.top();
      st.pop();
      match[poz] = i;
      match[i] = poz;
    }
  }
  prev[N + 1] = N;

  for (int i = 0; i < comm.size(); ++i) {
    if (comm[i] == 'L') {
      P = prev[P];
    } else if (comm[i] == 'R') {
      P = next[P];
    } else {
      //do the delete
      int x = match[P];
      if (x < P) {
        //deleting to the left
        next[prev[match[P]]] = next[P];
        prev[next[P]] = prev[match[P]];

        //cerr << "moving from " << P << " to " << next[P] << "\n";
        P = next[P];
      } else if (x > P) {
        //deleting to the right;
        prev[next[match[P]]] = prev[P];
        next[prev[P]] = next[match[P]];
        //cerr << "moving from " << P << " to " << next[match[P]] << "\n";
        P = next[match[P]];
      }
      if (P == N + 1) {
        P = prev[P];
      } else if (P == 0) {
        P = next[P];
      }
    }
    /*
    cerr << P << "\n";
    for (int k = next[0]; k <= N; k = next[k]) {
      cerr << k << " ";
    }
    cerr << "\n";
    for (int k = next[0]; k <= N; k = next[k]) {
      cerr << S[k];
    }
    cerr << "\n";
    */
  }
  for (int i = next[0]; i <= N; i = next[i]) {
    cout << S[i];
  }
  return 0;
}

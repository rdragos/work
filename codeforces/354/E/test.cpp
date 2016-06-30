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
const ll inf = 10005;


int getint(const string& S) {
  int x = 0, start = 0;
  int flag = 1;
  if (S[0] == '-') {
    flag = -1, start = 1;
  }
  for (int i = start; i < S.size(); ++i) {
    x = x * 10 + (S[i] - '0');
  }
  return x * flag;
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */


  int N, K; cin >> N >> K;

  vector<ll> V(N + 1);

  int non_det = 0;
  for (int i = 0; i <= N; ++i) {
    string S; cin >> S;
    if (S == "?") {
      V[i] = inf;
      non_det += 1;
    } else {
      V[i] = 1LL * getint(S);
    }
  }
  if (K == 0) {

    int rem = N + 1 - non_det;
    if(rem%2==1&&V[0]==inf) {
      cout << "Yes";
    } else if (V[0] == 0) {
      cout << "Yes";
    } else {
      cout << "No";
    }
    return 0;
  }
  vector<ll> primes{2750159, 4256233, 179424673, 2038074743, 982451653, 275604541};
  if (non_det != 0) {
    if ( (N+1) % 2 == 0) {
      cout << "Yes";
    } else {
      cout << "No";
    }
    return 0;
  } else {
    //is K a root?
    for (auto p: primes) {
      ll x = 1, sum = 0;
      for (int i = 0; i <= N; ++i) {
        sum = sum + x * V[i];
        sum %= p;
        x = (x * K) % p;
      }
      if (sum != 0) {
        cout << "No";
        return 0;
      }
    }
  }
  cout << "Yes";
  return 0;
}

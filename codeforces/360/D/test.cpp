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



vector<int> get_primes(int N) {
  vector<int> v(N + 1, 1);
  vector<int> primes;

  for (int i = 2; i < N; ++i) {
    if (v[i] == 0) {
      continue;
    }
    primes.push_back(i);
    for (ll j = 1LL * i * i; j < N; j += i) {
      v[j] = 0;
    }
  }
  return primes;
}

vector<int> get_dec(int X, vector<int>&primes) {

  vector<int> res;

  for (auto p: primes) {
    if (1LL * p * p > X) {
      break;
    }
    if (X % p) {
      continue;
    }
    int acc = 1;
    while(X % p == 0) {
      X /= p;
      acc *= p;
    }
    res.push_back(acc);
  }

  if (X > 1) {
    res.push_back(X);
  }
  return res;
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */
  ios_base::sync_with_stdio(false);
  int N, K; cin >> N >> K;
  vector <int> v(N);
  for (int i = 0; i < N; ++i) {
    cin >> v[i];
  }
  //cerr << K << "\n";
  vector <int> allPrimes = get_primes(K);

  vector<int> decK = get_dec(K, allPrimes);

  for (auto f: decK) {
    bool can = false;
    for (int i = 0; i < N; ++i) {
      if (v[i] % f == 0) {
        can = true;
        break;
      }
    }
    if (can == false) {
      cout << "No";
      return 0;
    }
  }
  cout << "Yes";
  return 0;
}

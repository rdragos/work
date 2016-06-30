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

bool pali(int x) {
  vector<int> v;
  while(x > 0) {
    v.push_back(x % 10);
    x /= 10;
  }
  if (v.size() % 2) {
    return false;
  }
  vector<int> rv(v);
  reverse(rv.begin(), rv.end());

  for (int i = 0; i < v.size(); ++i) {
    if (rv[i] != v[i]) {
      return false;
    }
  }
  return true;
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */
  string S; cin >> S;
  string rS = S; reverse(rS.begin(), rS.end());
  cout << S + rS;
  return 0;
}

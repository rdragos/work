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
#include <iomanip>

#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;
pair <bool, double> f(double L, double V1, double V2, double mid, int ngroups, double raw) {
  double tn = mid / V2;
  double ans = 0.0;

  for (int i = 0; i < ngroups; ++i) {
    double tmp_time = (L - mid) / V1 + mid / V2;
    ans = max(ans, tmp_time);
    L -= mid / 2.0;
  }
  if (ans > raw) {
    return make_pair(false, 1e9);
  } else {
    return make_pair(true, ans);
  }
}
int main() {
  ifstream cin("test.in");
  ofstream cout("test.out");
  int N; cin >> N;
  double L, V1, V2; cin >> L >> V1 >> V2;
  int K; cin >> K;

  double raw = L / V1; //without using the bus
  int ngroups = (N+K-1) / K;

  cout << fixed << setprecision(10);
  cout << raw << "\n";

  cerr << "groups: " << ngroups << "\n";
  double fixed_raw = raw;
  double lf = 0, rt = raw;
  for (int iter = 0; iter < 10; ++iter) {
    double mid = (lf + rt) / 2.0;
    pair <bool, double> tmp = f(L, V1, V2, mid, ngroups, fixed_raw);
    cerr << lf << " " << mid << " " << rt << " * " << tmp.first << " " << tmp.second << "\n";
    if (tmp.first == false) {
      rt = mid;
    } else {
      raw = tmp.second;
      lf = mid;
    }
  }
  cout << lf << " " << raw << "\n";
  return 0;
}

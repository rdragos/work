#include <cstdio>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;


int main() {
  ifstream cin("test.in");
  ofstream cout("test.out");

  int N; cin >> N;
  vector <int> v(N);
  for (int i = 0; i < N; ++i) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  //rotate(v.begin(), v.begin() + 5, v.end());

  int lg = 1;
  while(lg < N) {
    lg <<= 1;
  }

  for (int i = 0; i < N; ++i) {
    cerr << v[i] << " " ;
  }
  int answer = 0;
  for (int step = lg; step > 0; step >>= 1) {
    if (answer + step < N && v[answer + step] >= v[0]) {
      answer += step;
    }
  }
  cerr << "\n";
  cerr << (answer + 1) % N << "\n";
  return 0;
}

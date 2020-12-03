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
  ifstream cin("test.in");
  ofstream cout("test.out");

  vector<string> mat;
  string s;
  while(cin >> s) {
      mat.push_back(s);
  }
  vector<int> X{1, 1, 1, 1, 2};
  vector<int> Y{1, 3, 5, 7, 1};
  vector<int> Dx, Dy;

  int K = X.size();
  Dx.resize(K, 0);
  Dy.resize(K, 0);

  vector<int> answers(K, 0);

  int N = mat.size();
  int M = mat[0].size();

  for (int i = 0; i < N; i++) { 
      for (int k = 0; k < K; ++k) {
          if (Dx[k] < N) {
              answers[k] += (mat[Dx[k]][Dy[k]] == '#');
          }
          Dx[k] += X[k];
          Dy[k] += Y[k]; Dy[k] %= M;
      }
  }
  long long sol = 1;
  for (size_t k = 0; k < answers.size(); k++)
      sol *= answers[k];
  cout << sol << endl;

  return 0;
}

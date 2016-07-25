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

  string S; cin >> S;

  int bpart = 0;

  string digits = "";
  bool flag = false;
  int point = 0;

  for (int i = 0; i < S.size(); ++i) {
    if (flag) {
      bpart = bpart * 10 + (S[i] - '0');
    }
    if (S[i] == 'e') {
      flag = true;
    }
    else if (S[i] == '.') {
      point = i;
    }
    if (!flag && S[i] != '.') {
      digits += S[i];
    }
  }


  string answer = "";
  for (int i = 0; i < point; ++i) {
    answer += digits[i];
  }
  for (int i = point; i < digits.size(); ++i) {
    if (bpart == 0) {
      answer += ".";
    }
    bpart -= 1;
    answer += digits[i];
  }
  while(bpart > 0) {
    answer += "0";
    bpart -= 1;
  }
  cout << answer << "\n";
  return 0;
}

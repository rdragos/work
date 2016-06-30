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
char to_str(int x) {
  return char('0' + x);
}

void empty(vector<int>&v1, vector<int>&v2, bool &flag) {
  flag = false;
  for (auto d: v1) {
    v2.push_back(d);
  }
}
vector <int> decomp(int x) {
  vector <int> cnt(10, 0);
  while(x > 0) {
    cnt[x % 10] += 1;
    x /= 10;
  }
  return cnt;
}
int get_dig(const vector<int>&v) {
  int sum = 0;
  for (int i = 0; i < 10; ++i) {
    sum += v[i];
  }
  return sum;
}
void debug(vector<int>&v) {
  for (int i = 0; i < v.size(); ++i) {
    cerr << i << " " << v[i] << "\n";
  }
  cerr << "\n";
}
vector <int> remainder(const vector<int>&v1,
    const vector<int>&v2) {
  vector <int> vres(v1.size(), 0);
  //check if v2 is contained in v1;
  for (int i = 0; i < 10; ++i) {
    vres[i] = v1[i] - v2[i];
    if (vres[i] < 0) {
      return vector<int>{-1};
    }
  }
  return vres;
}

int get_cur(vector<int>&v, int poz) {
  for (int i = (poz == 1); i < 10; ++i) {
    if (v[i] > 0) {
      return i;
    }
  }
  return -1;
}
void erase_cur(vector<int>&v, int poz) {
  v[poz]--;
}
int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  string S; cin >> S;
  string P; cin >> P;

  int n = S.size();

  vector <int> cnt(10, 0);
  for (int i = 0; i < n; ++i) {
    cnt[S[i] - '0'] += 1;
  }

  vector <int> Pi;
  vector<int> cntP(10, 0);
  for (int i = 0; i < P.size(); ++i) {
    cntP[P[i] - '0'] += 1;
    Pi.push_back(P[i] - '0');
  }
  vector<int> gl_R;

  for (int i = 1; i <= n; ++i) {
    vector<int> v = decomp(i);
    vector<int> r = remainder(cnt, v);
    if (r.size() == 1) {
      continue;
    }
    if (get_dig(v) + get_dig(r) == n) {
      gl_R = remainder(r, cntP);
    }
  }
  //debug(gl_R);
  vector <int> answer;
  int orig_size = get_dig(gl_R);
  bool can_insert = true;
  bool deserve = false;

  for (int i = 0; i < Pi.size(); ++i) {
    if (Pi[i] == Pi[0]) {
      continue;
    }
    if (Pi[i] < Pi[0]) {
      deserve = true;
      break;
    } else {
      break;
    }
  }
  int dig = get_cur(gl_R, 1);
  //debug(gl_R);

  if ((dig == Pi[0] && deserve) || (dig > Pi[0] && Pi[0] != 0)) {
    empty(Pi, answer, can_insert);
    orig_size++;
  } else if (dig == -1) {
    empty(Pi, answer, can_insert);
    orig_size++;
  } else {
    answer.push_back(dig);
    erase_cur(gl_R, dig);
  }
  for (int i = 2; i <= orig_size; ++i) {
    int dig = get_cur(gl_R, i);
//    cerr << "dig? " << dig << "\n";
    if (can_insert) {
      if (dig < Pi[0]) {
        answer.push_back(dig);
        erase_cur(gl_R, dig);
      } else if (dig > Pi[0]) {
        for (auto d: Pi) {
          answer.push_back(d);
        }
        can_insert = false;
        orig_size++;
      } else if (dig == Pi[0] && deserve) {
        for (auto d: Pi) {
          answer.push_back(d);
        }
        orig_size++;
        can_insert = false;
      } else {
        answer.push_back(dig);
        erase_cur(gl_R, dig);
      }
    } else {
      erase_cur(gl_R, dig);
      answer.push_back(dig);
    }
  }

  if (can_insert) {
    for (auto d: Pi) {
      answer.push_back(d);
    }
  }
  for (auto d: answer) {
    cout << d;
  }
  return 0;
}

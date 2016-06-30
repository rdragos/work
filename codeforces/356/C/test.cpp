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



bool prime(int x) {

  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}
void write(int x) {
  cout << x << "\n";
  fflush(stdout);
}
void write(string s) {
  cout << s << "\n";
  fflush(stdout);
}

void solver() {

  int asked = 0;
  vector<int> answers;

  string response;
  for (int i = 2; i <= 50; ++i) {
    if (prime(i)) {
      write(i);
      cin >> response;
      if (response == "yes") {
        answers.push_back(i);
      }
      asked += 1;
    }
  }
  if (answers.size() == 0) {
    write("prime");
  }
  else if (answers.size() >= 2) {
    write("composite");
  } else {
    int x = answers[0];
    if (x * x <= 100) {
      write(x * x);
      cin >> response;
      if (response == "yes") {
        write("composite");
      } else {
        write("prime");
      }
    } else {
      write("prime");
    }
  }
}
int main() {
//  ifstream cin("test.in");
 // ofstream cout("test.out");
  solver();
  return 0;
}

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


struct Point {
  int x, y;
  char val;

  vector<cells> getDir() {
    vector<
  }
};


Point rotate(Point& other) {
  if (other.val == '*') {
    return Point('*');
  } else if (other.val == '-') {
    return Point('|');
  } else if (other.val == '|') {
    return Point('-');
  } else if (other.val == '>') {
    return Point('v');
  } else if (other.val == '<') {
    return Point('^');
  } else if (other.val == 'v') {
    return Point('<');
  } else if (other.val == 'L') {
    return Point('U');
  } else if (other.val == 'R') {
    return Point('D');
  } else if (other.val == 'U') {
    return Point('R');
  } else if (other.val == 'D') {
    return Point('L');
  }
}
vector<Point> eval(Point p, int rot) {

}
int main() {
  ifstream cin("test.in");
  ofstream cout("test.out");

  int N, M; cin >> N >> M;


  vector<string>V(N);
  for (int i = 0; i < N; ++i) {
    cin >> V[i];
  }
  return 0;
}

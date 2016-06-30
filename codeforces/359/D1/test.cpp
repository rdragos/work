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


struct Event {

  int x, y, type;

  Event() {}
  Event(int _x, int _y, int _type) {
    x = _x; y = _y;
    type = _type;
  }
  bool operator < (const Event& other) {
    if (x == other.x) {
      if (y == other.y) {
        return type < other.type;
      } else {
        return y < other.y;
      }
    } else {
      return x < other.x;
    }
  }
};

int main() {
  /*
  ifstream cin("test.in");
  ofstream cout("test.out");
  */

  int N, K; cin >> N >> K;

  vector<Event> events;
  vector<int> Ycoord;

  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;

    events.push_back(Event(x - K, y, 1));
    events.push_back(Event(x, y, -1));

    Ycoord.push_back(y);
    Ycoord.push_back(y - K);
  }

  sort(Ycoord.begin(), Ycoord.end());
  Ycoord.resize(unique(Ycoord.begin(), Ycoord.end()) - Ycoord.begin());

  sort(events.begin(), events.end());

  vector<ll> answer(N + 1, 0);
  vector<int> lastX(2 * N + 1, 0), cnt(2 * N + 1, 0);

  for (auto cur_ev: events) {
    int ind = lower_bound(Ycoord.begin(), Ycoord.end(), cur_ev.y - K) - Ycoord.begin();
    while(ind < Ycoord.size() && Ycoord[ind] < cur_ev.y) {
      ll dx = cur_ev.x - lastX[ind];
      ll dy = Ycoord[ind + 1] - Ycoord[ind];

      answer[cnt[ind]] += dx * dy;

      cnt[ind] += cur_ev.type;
      //cerr << "x: " << cur_ev.x << " y: " << cur_ev.y << " type: " << cur_ev.type << " cnt: " << cnt[ind] << "\n";
      lastX[ind] = cur_ev.x;
      ind += 1;
    }
  }

  for (int i = 1; i <= N; ++i) {
    cout << answer[i] << " " ;
  }
  return 0;
}

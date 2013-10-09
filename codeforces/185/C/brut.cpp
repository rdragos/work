#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

vector <pair <int, int> > p;

double dist(pair <int, int> &a, pair <int, int> &b) {
    return sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second));
}
int main() {
    freopen("test.out", "r", stdin);
    int x, y;
    while (cin >> x >> y) {
        p.push_back(make_pair(x, y));
    }

    sort(p.begin(), p.end());

    double d = 1000000000;

    int tot = 0;
    for (int i = 0; i < p.size(); ++i) {
        for (int j = i + 1; j < p.size(); ++j) {
            ++tot;
            if (p[j].first - p[i].first >= d)
                break;
            d = min(d, dist(p[i], p[j]));
        }
    }
    cout << tot << "\n";

    return 0;
}

#include <bits/stdc++.h>
#include <cmath>
#include <complex>

using namespace std;

#define ll long long
#define ld long double
#define cd complex<ld>
#define vd vector<ld>
#define vcd vector<cd>
#define vi vector<int>

const ld PI = acos(-1.0);

class FFT {

  const int LOG = 15;
  const int N = 1 << LOG;

  vi rev;
  vcd _root;
  vcd a, b;

  void init() {
    int hb = -1;
    rev.assign(N, 0);
    _root.assign(N, 0);

    for (int i = 1; i < N; ++i) {
      if ((i & (i - 1)) == 0) {
        ++hb;
      }
      rev[i] = rev[i ^ (1 << hb)];
      rev[i] |= (1 << (LOG - hb - 1));
    }
    for (int i = 0; i < N; ++i) {
      ld angle = 2.0 * PI * i / (1.0 * N);
      _root[i] = cd(cosl(angle), sinl(angle));
    }
  }
  cd root(int k, int n) {
    return _root[k * (N / n)];
  }
  void fft_rec(cd* a, int n, int left = 0, int right = 8) {
    if (n == 1) {
      return ;
    }
    fft_rec(a, n / 2, left, (left+right)/2);
    fft_rec(a + n / 2, n / 2, (left+right)/2 + 1, right);

    for (int k = 0; k < n / 2; ++k) {
      // A(wi) = A_even((wi) ^ 2) - wi * A_odd((wi)^2 );
      // A(wi) = A_even(w(2i)) - wi * A_odd(w(2i))
      // A(-wi) = A_even(w(2i)) + wi * A_odd(w(2i))
      cd w = root(k, n);
      cd x = a[k];
      cd y = w * a[k + n / 2];

      a[k] = x + y;
      a[k + n / 2] = x - y;
    }
  }
  void fft(vcd& a) {
    vcd na(N);
    for (int i = 0; i < N; ++i) {
      na[i] = a[rev[i]];
    }
    na.swap(a); // swaps the vector na and a
    fft_rec(&a[0], N);
  }

  void fft_inv(vcd& a) {
    fft(a);
    for (int i = 0; i < N; ++i) {
      a[i] /= N;
    }
    //now we have the identity matrix from the bottom to top
    reverse(a.begin() + 1, a.end());
  }
 public:
  FFT(vi _a, vi _b): a(N), b(N) {
    for (size_t i = 0; i < _a.size(); ++i) {
      a[i] = cd(_a[i], 0);
    }
    for (size_t i = 0; i < _b.size(); ++i) {
      b[i] = cd(_b[i], 0);
    }
  }

  vi start_mul() {
    init();

    fft(a);
    fft(b);

    vcd c(N);
    for (int i = 0; i < N; ++i) {
      c[i] = a[i] * b[i];
    }
    fft_inv(c);

    vi res(N);
    for (int i = 0; i < N; ++i) {
      res[i] = int(c[i].real() + 0.5);
    }
    return res;
  }
};
int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("test.in");
  ofstream cout("test.out");
#endif

  //input is given as following:"
  //first line: n (degree of the first poly)
  //second line: n integers representing the coefficients: a(0) + a(1) * X + a(2) * X ^ 2 + ... + a(n - 1) * X ^ (n-1)
  int n; cin >> n;
  vi a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  //third line: m (degree of the second poly)
  //fourth line: m integers b: b(0), b(1), .... b(m - 1)
  int m; cin >> m;
  vi b(m);
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }

  FFT F(a, b);
  vi res = F.start_mul();

  cout << "multiplied poly is:\n";
  for (int i = 0; i < (n - 1 + m); ++i) {
    cout << res[i] << " * " << "X^(" << i << ")";
    if (i != n - 1 + m - 1) {
      cout << " + ";
    }
  }
  return 0;
}

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <map>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;
typedef long long ll;

class StaticRMQ {
public:
  vector <ll> dat;
  int N;

  StaticRMQ(int n) {
    init(n);
  }

  void init(int n) {
    N = 1;

    while (N < n) N *= 2;

    for (int i = 0; i < 2 * N - 1; ++i) {
      dat.push_back(LONG_MAX);
    }
  }

  void update(int k, ll a) {
    k += N - 1;
    dat[k] = a;

    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  ll find_min(int l, int r) {
    return query(l, r, 0, 0, N);
  }

private:

  ll query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return LONG_MAX;

    if (a <= l && r <= b) {
      return dat[k];
    } else {
      ll vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
      ll vr = query(a, b, k * 2 + 2, (l + r) / 2, r);

      return min(vl, vr);
    }
  }
};

int main() {
  int N, Q;

  cin >> N >> Q;

  StaticRMQ rmq(N);

  vector<int> A;
  int a;
  for (int i = 0; i < N; ++i) {
    cin >> a;
    A.push_back(a);
    rmq.update(i, a);
  }

  int l, r;
  for (int i = 0; i < Q; ++i) {
    cin >> l >> r;

    ll v = rmq.find_min(l, r);

    cout << v << endl;
  }

  return 0;
}


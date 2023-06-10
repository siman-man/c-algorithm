#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <map>
#include <queue>
#include <set>
#include <string.h>
#include <vector>

using namespace std;
typedef long long ll;

const int MAX_N = 200'010;
const ll EMPTY_VALUE = -1;

class RangeUpdateQuery {
public:
  int N;
  ll dat[MAX_N];
  ll lazy[MAX_N];

  RangeUpdateQuery(int _N, ll init_value = 0) {
    this->N = _N;

    for (int i = 0; i < 2 * N; ++i) {
      dat[i] = init_value;
      lazy[i] = 0LL;
    }
  }

  void update(int l, int r, ll x) {
    _fill_value(l, r, x, 0, 0, N - 1);
  }

  ll find(int idx) {
    return _sum(idx, idx, 0, 0, N - 1);
  }

  ll find_min(int l, int r) {
    return _min(l, r, 0, 0, N - 1);
  }

private:
  void _fill_value(int a, int b, ll x, int idx, int l, int r) {
    if (r < a || b < l) return;

    _evaluate(idx, l, r);

    if (a <= l && r <= b) {
      lazy[idx] = x;
    } else {
      _fill_value(a, b, x, idx * 2 + 1, l, (l + r) / 2);
      _fill_value(a, b, x, idx * 2 + 2, (l + r) / 2 + 1, r);
    }
  }

  void _evaluate(int idx, int l, int r) {
    if (lazy[idx] == EMPTY_VALUE) {
      return;
    }

    dat[idx] = lazy[idx];

    if (r - l > 0) {
      lazy[2 * idx + 1] = lazy[idx];
      lazy[2 * idx + 2] = lazy[idx];
    }

    lazy[idx] = EMPTY_VALUE;
  }

  ll _sum(int a, int b, int idx, int l, int r) {
    if (r < a || b < l) {
      return 0LL;
    }

    _evaluate(idx, l, r);

    if (a <= l && r <= b) {
      return dat[idx];
    } else {
      ll value_left = _sum(a, b, idx * 2 + 1, l, (l + r) / 2);
      ll value_right = _sum(a, b, idx * 2 + 2, (l + r) / 2 + 1, r);

      return value_left + value_right;
    }
  }

  ll _min(int a, int b, int idx, int l, int r) {
    if (r < a || b < l) {
      return 0LL;
    }

    _evaluate(idx, l, r);

    if (a <= l && r <= b) {
      return dat[idx];
    } else {
      ll value_left = _sum(a, b, idx * 2 + 1, l, (l + r) / 2);
      ll value_right = _sum(a, b, idx * 2 + 2, (l + r) / 2 + 1, r);

      return (value_left < value_right) ? value_left : value_right;
    }
  }
};

int main() {
  return 0;
}
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

const ll MOD = 1000000007;

class RangeMaximumQuery {
public:
  int N;
  vector<int> dat;

  RangeMaximumQuery(int _N, int init_value) {
    this->N = 1;

    while (N < _N) {
      N *= 2;
    }

    for (int i = 0; i < 2 * N; ++i) {
      dat.push_back(init_value);
    }
  }

  void update(int idx, int val) {
    idx += n - 1;
    dat[idx] = val;

    while (idx > 0) {
      idx = (idx - 1) / 2;

      if (dat[idx * 2 + 1] > dat[idx * 2 + 2]) {
        dat[idx] = dat[idx * 2 + 1];
      } else {
        dat[idx] = dat[idx * 2 + 2];
      }
    }
  }

  int find_max(int l, int r) {
    return query(l, r, 0, 0, N - 1);
  }

private:

  void query(int a, int b, int idx, int l, int r) {
    if (r < a || b < l) return 0;

    if (a <= l && r <= b) {
      return dat[idx];
    } else {
      int vl = query(a, b, idx * 2 + 1, l, (l + r) / 2);
      int vr = query(a, b, idx * 2 + 2, (l + r) / 2 + 1, r);

      return (vl > vr) ? vl : vr;
    }
  }
};

int main() {

  return 0;
}
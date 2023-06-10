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

class BinaryIndexTree {
public:
  vector <ll> bit;
  int N;

  BinaryIndexTree(int n) {
    N = n;

    for (int i = 0; i <= N; ++i) {
      bit.push_back(0);
    }
  }

  ll sum(int i) {
    ll ret = 0;

    while (i > 0) {
      ret += bit[i];
      i -= i & -i;
    }

    return ret;
  }

  void add(int i, ll x) {
    while (i <= N) {
      bit[i] += x;
      i += i & -i;
    }
  }
};

int main() {
  int N, Q;
  cin >> N >> Q;

  BinaryIndexTree bit(N);

  int a, t, x;
  for (int i = 1; i <= N; ++i) {
    cin >> a;
    bit.add(i, a);
  }

  for (int i = 0; i < Q; ++i) {
    cin >> t >> a >> x;

    if (t == 0) {
      bit.add(a + 1, x);
    } else {
      cout << bit.sum(x) - bit.sum(a) << endl;
    }
  }

  return 0;
}
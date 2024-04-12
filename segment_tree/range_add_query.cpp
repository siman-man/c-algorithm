#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <climits>
#include <map>
#include <queue>
#include <set>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;

const int MAX_N = 100000;

class RangeAddQuery {
public:
  vector <ll> bit0;
  vector <ll> bit1;

  RangeAddQuery(int N) {
    bit0.resize(N + 1);
    bit1.resize(N + 1);
  }

  void update(int l, int r, ll x) {
    add(bit0, l, -x * (l - 1));
    add(bit1, l, x);
    add(bit0, r + 1, x * r);
    add(bit1, r + 1, -x);
  }

  ll get(int i) {
    return get(i, i);
  }

  ll get(int l, int r) {
    ll res = 0;
    res += sum(bit0, r) + sum(bit1, r) * r;
    res -= sum(bit0, l - 1) + sum(bit1, l - 1) * (l - 1);

    return res;
  }

private:
  void add(vector <ll> &b, int i, ll v) {
    while (i <= MAX_N) {
      b[i] += v;
      i += i & -i;
    }
  }

  ll sum(vector <ll> &b, int i) {
    ll s = 0;
    while (i > 0) {
      s += b[i];
      i -= i & -i;
    }
    return s;
  }
};

int main() {
  RangeAddQuery raq(MAX_N);

  cout << raq.get(1, MAX_N) << endl;
  raq.update(1, 10, 5);
  cout << raq.get(2) << endl;

  return 0;
}

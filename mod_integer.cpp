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
const ll MOD = 1000000007;
ll fac[MAX_N];
ll inv[MAX_N];
ll finv[MAX_N];

class ModInteger {
public:
  ModInteger(int N) {
    fac[0] = fac[1] = 1;
    inv[0] = inv[1] = 1;
    finv[0] = finv[1] = 1;

    for (int i = 2; i <= N; ++i) {
      fac[i] = fac[i - 1] * i % MOD;
      inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
      finv[i] = finv[i - 1] * inv[i] % MOD;
    }
  }

  ll combination(int n, int k) {
    if (n < k) return 0LL;
    if (n < 0 || k < 0) return 0LL;

    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
  }

  ll permutation(int n, int k = -1) {
    if (k == -1) k = n;
    if (n < k) return 0LL;
    if (n < 0 || k < 0) return 0LL;

    return fac[n] * (finv[n - k] % MOD) % MOD;
  }

  ll repeated_combination(int n, int k) {
    return combination(n + k - 1, k);
  }
};

int main() {
  return 0;
}
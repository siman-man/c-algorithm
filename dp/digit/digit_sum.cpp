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

// 数値の桁の総和が D で割り切れるものの数をカウントする
int main() {
  string K;
  int D;
  cin >> K;
  cin >> D;
  int L = K.size();
  ll MOD = 1000000007;

  ll dpA[L + 1][D];
  ll dpB[L + 1][D];
  memset(dpA, 0, sizeof(dpA));
  memset(dpB, 0, sizeof(dpB));

  dpA[0][0] = 1;

  for (int i = 0; i < L; ++i) {
    ll n = K[i] - '0';

    for (int j = 0; j < D; ++j) {
      if (dpA[i][j] > 0) {
        dpA[i + 1][(j + n) % D] = dpA[i][j];

        if (i > 0) {
          for (int k = 0; k < n; ++k) {
            dpB[i + 1][(j + k) % D] += 1;
          }
        }
      }

      if (dpB[i][j] > 0) {
        for (int k = 0; k <= 9; ++k) {
          dpB[i + 1][(j + k) % D] += dpB[i][j];
          dpB[i + 1][(j + k) % D] %= MOD;
        }
      }
    }

    for (int k = 1; k <= 9; ++k) {
      if (i == 0 && k >= n) continue;
      dpB[i + 1][k % D] += 1;
    }
  }

  cout << (dpA[L][0] + dpB[L][0]) % MOD << endl;

  return 0;
}

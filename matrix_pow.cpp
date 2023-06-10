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
typedef vector <ll> vec;
typedef vector <vec> mat;

ll N, K;
ll MOD = 1'000'000'007;

mat mul(mat &A, mat &B) {
  mat C(A.size(), vec(B[0].size()));

  for (int i = 0; i < A.size(); ++i) {
    for (int k = 0; k < B.size(); ++k) {
      for (int j = 0; j < B[0].size(); ++j) {
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
      }
    }
  }

  return C;
}

// 行列の累乗
mat pow(mat A, ll n) {
  mat B(A.size(), vec(A.size()));

  for (int i = 0; i < A.size(); ++i) {
    B[i][i] = 1;
  }

  while (n > 0) {
    if (n & 1) B = mul(B, A);
    A = mul(A, A);
    n >>= 1;
  }

  return B;
}

int main() {
  cin >> N >> K;

  mat M(N);

  ll a;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> a;
      M[i].push_back(a);
    }
  }

  mat C = pow(M, K);
  ll ans = 0;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      ans = (ans + C[i][j]) % MOD;
    }
  }

  cout << ans << endl;

  return 0;
}

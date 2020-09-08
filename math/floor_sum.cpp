#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

ll floor_sum(ll n, ll m, ll a, ll b) {
  long long ans = 0;

  if (a >= m) {
    ans += (n - 1) * n * (a / m) / 2;
    a %= m;
  }

  if (b >= m) {
    ans += n * (b / m);
    b %= m;
  }

  ll y_max = (a * n + b) / m;
  ll x_max = (y_max * m - b);

  if (y_max == 0) return ans;

  ans += (n - (x_max + a - 1) / a) * y_max;
  ans += floor_sum(y_max, a, m, (a - x_max % a) % a);

  return ans;
}

int main() {
  int T;
  cin >> T;

  int N, M, A, B;
  for (int i = 0; i < T; ++i) {
    cin >> N >> M >> A >> B;

    cout << floor_sum(N, M, A, B) << endl;
  }

  return 0;
}

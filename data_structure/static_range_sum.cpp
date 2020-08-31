#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

// 累積和
vector<ll> cumulative_sum(vector<int> &A) {
  vector<ll> res;
  res.push_back(0);

  for (int a : A) {
    res.push_back(res.back() + a);
  }

  return res;
}

int main() {
  int N, Q;
  cin >> N >> Q;

  int a;
  vector<int> A;

  for (int i = 0; i < N; ++i) {
    cin >> a;
    A.push_back(a);
  }

  vector<ll> RUI = cumulative_sum(A);

  int l, r;
  for (int i = 0; i < Q; ++i) {
    cin >> l >> r;

    cout << RUI[r] - RUI[l] << endl;
  }

  return 0;
}
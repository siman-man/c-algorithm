#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
typedef long long ll;

int main() {
  int Q;
  cin >> Q;
  map <ll, ll> memo;

  ll type, k, v;
  for (int i = 0; i < Q; ++i) {
    cin >> type;

    switch (type) {
      case 0:
        cin >> k >> v;
        memo[k] = v;
        break;
      case 1:
        cin >> k;
        cout << memo[k] << endl;
        break;
      default:
        break;
    }
  }

  return 0;
}
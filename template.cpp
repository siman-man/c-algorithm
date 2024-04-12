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

const ll MOD = 1000000007;

struct Node {
  int id;
  int cnt;

  Node(int id = -1, int cnt = -1) {
    this->id = id;
    this->cnt = cnt;
  }

  bool operator>(const Node &n) const {
    return cnt < n.cnt;
  }
};

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  priority_queue <Node, vector<Node>, greater<Node>> pque;
  cout << fixed << setprecision(10) << 0.12 << endl;

  return 0;
}
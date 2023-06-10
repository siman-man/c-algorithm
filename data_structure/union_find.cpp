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

const int MAX_N = 200000;

class UnionFind {
public:
  vector<int> _parent;
  vector<int> _rank;
  vector<int> _size;

  UnionFind(int n) {
    for (int i = 0; i < n; ++i) {
      _parent.push_back(i);
      _rank.push_back(0);
      _size.push_back(1);
    }
  }

  int find(int x) {
    if (_parent[x] == x) {
      return x;
    } else {
      return _parent[x] = find(_parent[x]);
    }
  }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;

    if (_rank[x] < _rank[y]) {
      _parent[x] = y;
      _size[y] += _size[x];
    } else {
      _parent[y] = x;
      _size[x] += _size[y];
      if (_rank[x] == _rank[y]) ++_rank[x];
    }
  }

  bool same(int x, int y) {
    return find(x) == find(y);
  }

  int size(int x) {
    return _size[find(x)];
  }
};

int main() {
  int N, Q;

  cin >> N >> Q;
  UnionFind uf;
  uf.init(MAX_N);

  int t, u, v;
  for (int i = 0; i < Q; ++i) {
    cin >> t >> u >> v;

    if (t == 0) {
      uf.unite(u, v);
    } else {
      if (uf.same(u, v)) {
        cout << 1 << endl;
      } else {
        cout << 0 << endl;
      }
    }
  }

  return 0;
}

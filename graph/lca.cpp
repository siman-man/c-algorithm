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

const int MAX_V = 500000;

struct Node {
  int v;
  int depth;

  Node(int v = -1, int depth = -1) {
    this->v = v;
    this->depth = depth;
  }

  bool operator<(const Node &n) const {
    return depth < n.depth;
  }
};

class StaticRMQ {
public:
  vector <Node> dat;
  int N;

  void init(int n) {
    N = 1;

    while (N < n) N *= 2;

    for (int i = 0; i < 2 * N - 1; ++i) {
      dat.push_back(Node(-1, MAX_V));
    }
  }

  void update(int k, Node a) {
    k += N - 1;
    dat[k] = a;

    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  ll find_min(int l, int r) {
    return query(l, r, 0, 0, N).v;
  }

private:

  Node query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return Node(-1, MAX_V);

    if (a <= l && r <= b) {
      return dat[k];
    } else {
      Node vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
      Node vr = query(a, b, k * 2 + 2, (l + r) / 2, r);

      return min(vl, vr);
    }
  }
};

class LCA {
public:
  vector<int> vs;
  vector<int> depth;
  vector<int> id;
  vector <vector<int> > G;
  StaticRMQ rmq;

  LCA(int N, vector <vector<int> > _G) {
    G = _G;
    int k = 0;
    vs = vector<int>(2 * N - 1);
    depth = vector<int>(2 * N - 1);
    id = vector<int>(N, -1);
    dfs(0, -1, 0, k);
    rmq.init(k);

    for (int i = 0; i < k; ++i) {
      rmq.update(i, Node(vs[i], depth[i]));
    }
  }

  int find_parent(int u, int v) {
    return rmq.find_min(min(id[u], id[v]), max(id[u], id[v]));
  }

private:
  void dfs(int v, int p, int d, int &k) {
    id[v] = k;
    vs[k] = v;
    depth[k++] = d;

    for (int i = 0; i < G[v].size(); ++i) {
      if (G[v][i] != p) {
        dfs(G[v][i], v, d + 1, k);
        vs[k] = v;
        depth[k++] = d;
      }
    }
  }
};

int main() {
  int N, Q;
  cin >> N >> Q;
  int p;
  vector<vector<int> > G(N);
  for (int i = 1; i <= N - 1; ++i) {
    cin >> p;
    G[i].push_back(p);
    G[p].push_back(i);
  }

  LCA lca(N, G);
  int l, r;
  for (int i = 0; i < Q; ++i) {
    cin >> l >> r;
    int p = lca.find_parent(l, r);

    cout << p << endl;
  }

  return 0;
}
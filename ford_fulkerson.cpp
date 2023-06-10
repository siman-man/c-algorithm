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

const int INF = INT_MAX;

struct Edge {
  int to;
  int cap;
  int rev;

  Edge(int to = -1, int cap = -1, int rev = -1) {
    this->to = to;
    this->cap = cap;
    this->rev = rev;
  }
};

const int MAX_V = 100;
bool used[MAX_V];
int V, E;
vector <Edge> G[MAX_V];

void add_edge(int from, int to, int cap) {
  G[from].push_back(Edge(to, cap, G[to].size()));
  G[to].push_back(Edge(from, 0, G[from].size() - 1));
}

int dfs(int v, int t, int f) {
  if (v == t) return f;

  used[v] = true;

  for (int i = 0; i < G[v].size(); ++i) {
    Edge *e = &G[v][i];

    if (!used[e->to] && e->cap > 0) {
      int d = dfs(e->to, t, min(f, e->cap));
      if (d > 0) {
        e->cap -= d;
        G[e->to][e->rev].cap += d;
        return d;
      }
    }
  }

  return 0;
}

int max_flow(int s, int t) {
  int flow = 0;
  for (;;) {
    memset(used, 0, sizeof(used));
    int f = dfs(s, t, INF);
    if (f == 0) return flow;
    flow += f;
  }
}

int main() {
  memset(used, false, sizeof(used));

  cin >> V >> E;

  int u, v, c;
  for (int i = 0; i < E; ++i) {
    cin >> u >> v >> c;

    add_edge(u, v, c);
  }

  cout << max_flow(0, V - 1) << endl;

  return 0;
}
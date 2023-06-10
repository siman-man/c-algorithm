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

typedef vector <vector<int>> Graph;

// 強連結成分分解ライブラリ
class StronglyConnectedComponent {
public:
  Graph G;
  Graph rG;
  Graph cG;
  vector<int> vs;
  vector<bool> used;
  vector<int> componentId;
  int componentCount;
  int V;

  StronglyConnectedComponent(int V) {
    this->V = V;
    used = vector<bool>(V);
    componentId = vector<int>(V);
    G = Graph(V);
    rG = Graph(V);
  }

  void add_edge(int from, int to) {
    assert(0 <= from && from < V);
    assert(0 <= to && to < V);

    G[from].push_back(to);
    rG[to].push_back(from);
  }

  void run() {
    fill(used.begin(), used.end(), false);
    componentCount = 0;
    vs.clear();

    for (int v = 0; v < V; ++v) {
      if (used[v]) continue;

      dfs(v);
    }

    fill(used.begin(), used.end(), false);

    for (int i = vs.size() - 1; i >= 0; --i) {
      int v = vs[i];
      if (used[v]) continue;

      cG.push_back(vector<int>());
      rdfs(v, componentCount++);
    }
  }

private:
  void dfs(int v) {
    used[v] = true;

    for (int i = 0; i < (int) G[v].size(); ++i) {
      int u = G[v][i];

      if (used[u]) continue;

      dfs(u);
    }

    vs.push_back(v);
  }

  void rdfs(int v, int k) {
    used[v] = true;
    componentId[v] = k;
    cG[k].push_back(v);

    for (int i = 0; i < (int) rG[v].size(); ++i) {
      int u = rG[v][i];

      if (used[u]) continue;

      rdfs(u, k);
    }
  }
};

const int MAX_V = 2010;
int N, D;
bool answer[MAX_V];
StronglyConnectedComponent scc(MAX_V);

void add_clause(int i, bool f, int j, bool g) {
  assert(0 <= i && i < N);
  assert(0 <= j && j < N);
  scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
  scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
}

bool satisfiable() {
  scc.run();
  memset(answer, false, sizeof(answer));

  for (int i = 0; i < N; ++i) {
    if (scc.componentId[2 * i] == scc.componentId[2 * i + 1]) return false;
    answer[i] = scc.componentId[2 * i] < scc.componentId[2 * i + 1];
  }

  return true;
}

int main() {
  cin >> N >> D;

  int X[N];
  int Y[N];

  int x, y;
  for (int i = 0; i < N; ++i) {
    cin >> x >> y;
    X[i] = x;
    Y[i] = y;
  }

  for (int i = 0; i < N; ++i) {
    int x1 = X[i];
    int y1 = Y[i];

    for (int j = i + 1; j < N; ++j) {
      if (i == j) continue;

      int x2 = X[j];
      int y2 = Y[j];

      if (abs(x1 - x2) < D) {
        add_clause(i, false, j, false);
      }

      if (abs(x1 - y2) < D) {
        add_clause(i, false, j, true);
      }

      if (abs(y1 - x2) < D) {
        add_clause(i, true, j, false);
      }

      if (abs(y1 - y2) < D) {
        add_clause(i, true, j, true);
      }
    }
  }

  if (satisfiable()) {
    cout << "Yes" << endl;

    for (int i = 0; i < N; ++i) {
      if (answer[i]) {
        cout << X[i] << endl;
      } else {
        cout << Y[i] << endl;
      }
    }
  } else {
    cout << "No" << endl;
    return 0;
  }

  return 0;
}

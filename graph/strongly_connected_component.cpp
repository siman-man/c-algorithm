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
    assert(0 <= from < V);
    assert(0 <= to < V);

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

    for (int i = 0; i < G[v].size(); ++i) {
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

    for (int i = 0; i < rG[v].size(); ++i) {
      int u = rG[v][i];

      if (used[u]) continue;

      rdfs(u, k);
    }
  }
};

int main() {
  int N, M;
  cin >> N >> M;

  StronglyConnectedComponent scc(N);
  int from, to;
  for (int i = 0; i < M; ++i) {
    cin >> from >> to;
    scc.add_edge(from, to);
  }

  scc.run();
  int cnt = scc.componentCount;

  cout << cnt << endl;
  for (int i = 0; i < cnt; ++i) {
    vector<int> T = scc.cG[i];
    cout << T.size() << " ";

    for (int j = 0; j < T.size(); ++j) {
      cout << T[j];

      if (j != T.size() - 1) {
        cout << " ";
      } else {
        cout << endl;
      }
    }
  }

  return 0;
}

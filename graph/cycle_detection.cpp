#include <iostream>
#include <stack>
#include <string.h>
#include <vector>

using namespace std;

typedef vector <vector<int>> Graph;
const int MAX_N = 100000;

int root;
bool visited[MAX_N];
bool finished[MAX_N];

void dfs(int u, int parent, const Graph &G, stack<int> &path) {
  visited[u] = true;
  path.push(u);

  for (int v : G[u]) {
    if (v == parent) continue;
    if (finished[v]) continue;

    if (visited[v] && !finished[v]) {
      root = v;
      return;
    }

    dfs(v, u, G, path);

    if (root != -1) return;
  }

  path.pop();
  finished[u] = true;
}

vector<int> cycle_detection(int start, const Graph &G) {
  root = -1;
  memset(visited, false, sizeof(visited));
  memset(finished, false, sizeof(finished));
  stack<int> path;

  dfs(start, -1, G, path);

  vector<int> res;

  while (!path.empty()) {
    res.push_back(path.top());
    path.pop();
  }

  return res;
}

int main() {
  int N, M;
  cin >> N >> M;
  Graph G(N + 1);

  int a, b;
  for (int i = 0; i < M; ++i) {
    cin >> a >> b;

    G[a].push_back(b);
  }

  vector<int> path = cycle_detection(1, G);

  if (path.empty()) {
    cout << -1 << endl;
  } else {
    int minV = INT_MAX;
    vector<int> res;

    for (int v : path) {
      vector<int> p = cycle_detection(v, G);
      int s = p.size();

      if (minV > s) {
        minV = s;
        res = p;
      }
    }

    cout << minV << endl;
    for (int v : res) {
      cout << v << endl;
    }
  }

  return 0;
}

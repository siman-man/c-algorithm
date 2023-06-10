#include <iostream>
#include <stack>
#include <string.h>
#include <vector>

using namespace std;

typedef vector <vector<int>> Graph;

vector<int> tsort(Graph G, int start, int end) {
  vector<int> ret;

  int degree[end];
  memset(degree, 0, sizeof(degree));

  for (int from = start; from < end; from++) {
    for (int i = 0; i < G[from].size(); i++) {
      int to = G[from][i];
      degree[to]++;
    }
  }

  stack<int> root;

  for (int i = start; i < end; i++) {
    if (degree[i] == 0) {
      root.push(i);
    }
  }

  while (!root.empty()) {
    int from = root.top();
    root.pop();

    ret.push_back(from);

    for (int i = 0; i < G[from].size(); i++) {
      int to = G[from][i];
      degree[to]--;

      if (degree[to] == 0) {
        root.push(to);
      }
    }
  }

  return ret;
}

int main() {
  int V, E;
  cin >> V >> E;

  Graph G(V);

  int s, t;

  for (int i = 0; i < E; ++i) {
    cin >> s >> t;

    G[s].push_back(t);
  }

  vector<int> res = tsort(G, 0, V);

  if (res.size() != V) {
    // tsort failed.
    cout << -1 << endl;
  }

  for (int i = 0; i < res.size(); ++i) {
    cout << res[i] << endl;
  }

  return 0;
}

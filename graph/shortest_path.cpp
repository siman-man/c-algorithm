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

struct Edge {
  int to;
  ll cost;

  Edge(int to = -1, ll cost = -1) {
    this->to = to;
    this->cost = cost;
  }
};

struct Node {
  int v;
  ll cost;
  int parent;

  Node(int v = -1, ll cost = -1, int parent = -1) {
    this->v = v;
    this->cost = cost;
    this->parent = parent;
  }

  bool operator>(const Node &n) const {
    return cost > n.cost;
  }
};

int main() {
  int N, M, S, T;
  cin >> N >> M >> S >> T;
  vector <Edge> E[N];

  int a, b;
  ll c;
  for (int i = 0; i < M; ++i) {
    cin >> a >> b >> c;

    E[a].push_back(Edge(b, c));
  }

  priority_queue <Node, vector<Node>, greater<Node>> pque;
  bool visited[N];
  memset(visited, false, sizeof(visited));
  int beforeNode[N];
  memset(beforeNode, -1, sizeof(beforeNode));

  pque.push(Node(S, 0));
  ll ans = LLONG_MAX;
  vector<int> path;

  while (!pque.empty()) {
    Node node = pque.top();
    pque.pop();

    if (visited[node.v]) continue;
    visited[node.v] = true;
    beforeNode[node.v] = node.parent;

    if (node.v == T) {
      ans = node.cost;
      int cur = node.v;

      while (cur != -1) {
        path.push_back(cur);
      }

      path.push_back(S);

      break;
    }

    for (int i = 0; i < E[node.v].size(); ++i) {
      Edge edge = E[node.v][i];

      pque.push(Node(edge.to, node.cost + edge.cost, node.v));
    }
  }

  if (ans == LLONG_MAX) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}
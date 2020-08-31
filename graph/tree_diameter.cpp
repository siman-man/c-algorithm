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

struct Edge {
  int to;
  ll cost;

  Edge(int to = -1, ll cost = -1) {
    this->to = to;
    this->cost = cost;
  }
};

vector <Edge> E[MAX_V];

struct Node {
  int v;
  ll cost;
  vector<int> path;

  Node(int v = -1, ll cost = -1) {
    this->v = v;
    this->cost = cost;
  }
};

class Tree {
public:
  int nodeCnt;

  Tree(int nodeCnt = MAX_V) {
    this->nodeCnt = nodeCnt;
  }

  void addEdge(int from, int to, ll cost = 1) {
    E[from].push_back(Edge(to, cost));
  }

  Node diameter(int from = 0) {
    int u = findFarthestVertex(from);
    int v = findFarthestVertex(u);

    return findPath(u, v);
  }

  Node findPath(int from, int to) {
    queue <Node> que;
    Node root(from, 0);
    root.path.push_back(from);
    que.push(root);
    bool visited[MAX_V];
    memset(visited, false, sizeof(visited));

    while (!que.empty()) {
      Node node = que.front();
      que.pop();

      if (visited[node.v]) continue;
      visited[node.v] = true;

      if (node.v == to) {
        return node;
      }

      for (int i = 0; i < E[node.v].size(); ++i) {
        Edge edge = E[node.v][i];

        Node next(edge.to, node.cost + edge.cost);
        next.path = node.path;
        next.path.push_back(edge.to);

        que.push(next);
      }
    }

    return Node();
  }

private:

  int findFarthestVertex(int from) {
    queue <Node> que;
    que.push(Node(from, 0));
    bool visited[MAX_V];
    memset(visited, false, sizeof(visited));

    ll maxCost = INT_MIN;
    int farthestV = -1;

    while (!que.empty()) {
      Node node = que.front();
      que.pop();

      if (visited[node.v]) continue;
      visited[node.v] = true;

      if (maxCost < node.cost) {
        maxCost = node.cost;
        farthestV = node.v;
      }

      for (int i = 0; i < E[node.v].size(); ++i) {
        Edge edge = E[node.v][i];

        Node next(edge.to, node.cost + edge.cost);
        que.push(next);
      }
    }

    return farthestV;
  }
};

int main() {
  int N;
  cin >> N;

  Tree tree;
  int a, b, c;
  for (int i = 0; i < N - 1; ++i) {
    cin >> a >> b >> c;

    tree.addEdge(a, b, c);
    tree.addEdge(b, a, c);
  }

  Node node = tree.diameter();
  vector<int> path = node.path;

  cout << node.cost << " " << path.size() << endl;
  for (int i = 0; i < path.size(); ++i) {
    cout << path[i];

    if (i != path.size() - 1) {
      cout << " ";
    }
  }

  cout << endl;

  return 0;
}
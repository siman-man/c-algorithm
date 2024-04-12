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

struct NodePointer {
  int parent;
  int command;
  int value;

  NodePointer(int parent = -1, int command = 0, int value = 0) {
    this->parent = parent;
    this->command = command;
    this->value = value;
  }

  bool operator>(const NodePointer &np) const {
    return value < np.value;
  }
};

struct Node {
  int parent;
  int command;
  int y;
  int x;
  int value;

  Node(int parent = -1, int command = -1, int y = -1, int x = -1, int value = 0) {
    this->parent = parent;
    this->command = command;
    this->y = y;
    this->x = x;
    this->value = value;
  }

  bool operator>(const Node &n) const {
    return value < n.value;
  }
};

constexpr int MAX_NODE_NUM = 100000;
Node g_nodes[MAX_NODE_NUM];

vector<int> beam() {
  queue<int> que;
  int depth_limit = 10;
  int node_num = 0;
  int best_node_id = 0;

  for (int depth = 0; depth < depth_limit; ++depth) {
    priority_queue <Node, vector<Node>, greater<Node>> pque;

    while (not que.empty()) {
      int node_id = que.front();
      que.pop();
      Node &node = g_nodes[node_id];
    }

    int beam_width = 100;
    for (int i = 0; i < beam_width && not pque.empty(); ++i) {
      Node node = pque.top();
      pque.pop();

      Node next = node;
      g_nodes[node_num] = next;
      ++node_num;
    }
  }

  vector<int> commands;
  int cur_node_id = best_node_id;
  while (cur_node_id != 0) {
    Node &node = g_nodes[cur_node_id];
    commands.push_back(node.command);
    cur_node_id = node.parent;
  }

  return commands;
}

int main() {
  return 0;
}

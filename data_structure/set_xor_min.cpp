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

const int ROOT_NODE_ID = 0;
const int MAX_BIT_LENGTH = 30;
const int MAX_ELEMENT_NUM = 500000;
const int MAX_NODE_NUM = MAX_ELEMENT_NUM * MAX_BIT_LENGTH;
const int NODE_EMPTY = -1;

struct Node {
  int cnt;
  bool isEnd;
  int children[2];

  Node(int cnt = 0) {
    this->cnt = cnt;
    this->isEnd = false;
    memset(children, NODE_EMPTY, sizeof(children));
  }
};

Node nodes[MAX_NODE_NUM];

class IntTrie {
public:
  int bitLength;
  int mask;
  int nodeId;
  Node root;

  IntTrie(int bitLength = MAX_BIT_LENGTH) {
    this->nodeId = ROOT_NODE_ID;
    this->bitLength = bitLength;
    this->root = Node();
    this->mask = (1 << bitLength) - 1;
    nodes[ROOT_NODE_ID] = this->root;
  }

  void insert(int x) {
    if (isExist(x)) return;

    Node *node = &nodes[ROOT_NODE_ID];

    for (int i = bitLength; i >= 0; --i) {
      int v = (x >> i) & 1;

      if (node->children[v] == NODE_EMPTY) {
        node->children[v] = buildNode();
      }

      node = &nodes[node->children[v]];
      node->cnt++;
    }

    node->isEnd = true;
  }

  void remove(int x) {
    if (!isExist(x)) return;

    Node *node = &nodes[ROOT_NODE_ID];

    for (int i = bitLength; i >= 0; --i) {
      int v = (x >> i) & 1;
      node = &nodes[node->children[v]];
      node->cnt = max(0, node->cnt - 1);
    }

    node->isEnd = false;
  }

  bool isExist(int x) {
    Node *node = &nodes[ROOT_NODE_ID];

    for (int i = bitLength; i >= 0; --i) {
      int v = (x >> i) & 1;

      if (node->children[v] == NODE_EMPTY) return false;

      node = &nodes[node->children[v]];

      if (node->cnt == 0) return false;
    }

    return node->isEnd;
  }

  int min(int x) {
    int res = x;
    Node *node = &nodes[ROOT_NODE_ID];

    for (int i = bitLength; i >= 0; --i) {
      int v = (x >> i) & 1;

      if (node->children[v] != NODE_EMPTY && nodes[node->children[v]].cnt > 0) {
        res &= mask ^ (1 << i);
        node = &nodes[node->children[v]];
      } else if (node->children[v ^ 1] != NODE_EMPTY && nodes[node->children[v ^ 1]].cnt > 0) {
        res |= (1 << i);
        node = &nodes[node->children[v ^ 1]];
      } else {
        return res;
      }
    }

    return res;
  }

private:
  int buildNode() {
    nodeId++;
    nodes[nodeId] = Node();

    return nodeId;
  }
};

int main() {
  int Q;
  cin >> Q;

  IntTrie it;

  int type, x;
  for (int i = 0; i < Q; ++i) {
    cin >> type >> x;

    switch (type) {
      case 0:
        it.insert(x);
        break;
      case 1:
        it.remove(x);
        break;
      case 2:
        cout << it.min(x) << endl;
        break;
      default:
        break;
    }
  }

  return 0;
}

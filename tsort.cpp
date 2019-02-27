#include <iostream>
#include <stack>
#include <string.h>
#include <vector>

using namespace std;

vector<int> tsort(int v, vector<int> g[], bool zero_index = false) {
  vector<int> ret;

  int start = zero_index ? 0 : 1;
  int end = zero_index ? v : v + 1;
  int degree[end];
  memset(degree, 0, sizeof(degree));

  for (int from = start; from < end; from++) {
    for (int i = 0; i < g[from].size(); i++) {
      int to = g[from][i];
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

    for (int i = 0; i < g[from].size(); i++) {
      int to = g[from][i];
      degree[to]--;

      if (degree[to] == 0) {
        root.push(to);
      }
    }
  }

  return ret;
}

int main() {

  return 0;
}
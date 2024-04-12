#include <algorithm>
#include <vector>

class LowLink {
public:
  std::vector<int> ord;
  std::vector<int> low;
  std::vector <std::pair<int, int>> bridge;
  std::vector<int> joint_list;
  std::vector<bool> joint_or_not;
  std::vector <std::vector<int>> G;

  LowLink(int N) {
    ord.resize(N, -1);
    low.resize(N, -1);
    G.resize(N, std::vector<int>());
    k = 0;
    joint_or_not.resize(N, false);
  }

  LowLink(const std::vector <std::vector<int>> &G) {
    ord.resize(G.size(), -1);
    low.resize(G.size(), -1);
    this->G = G;

    build();
  }

  void build() {
    k = 0;
    joint_or_not.resize(G.size(), false);
    bridge.clear();

    for (int v = 0; v < (int) G.size(); ++v) {
      if (ord[v] == -1) {
        dfs(v);
      }
    }
  }

  void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }

  bool is_bridge(int u, int v) {
    if (ord[u] > ord[v]) {
      std::swap(u, v);
    }
    return ord[u] < low[v];
  }

  bool is_joint(int v) {
    return std::find(joint_list.begin(), joint_list.end(), v) != joint_list.end();
  }

private:
  int k;

  void dfs(int v, int parent = -1) {
    ord[v] = k++;
    low[v] = ord[v];
    bool is_joint = false;
    int cnt = 0;

    for (int u : G[v]) {
      if (u == parent) {
        continue;
      }
      if (ord[u] == -1) {
        ++cnt;
        dfs(u, v);
        low[v] = std::min(low[v], low[u]);
        if (parent != -1 && ord[v] <= low[u]) {
          is_joint = true;
        }
        if (ord[v] < low[u]) {
          bridge.emplace_back(std::minmax(u, v));
        }
      } else {
        low[v] = std::min(low[v], ord[u]);
      }
    }
    if (parent == -1 && cnt > 1) {
      is_joint = true;
    }
    joint_or_not[v] = is_joint;
    if (is_joint) {
      joint_list.push_back(v);
    }
  }
};

int main() {
  return 0;
}
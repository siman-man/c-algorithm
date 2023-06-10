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

const int INF = INT_MAX;

struct Edge {
  int to;
  int cap;
  int rev;

  Edge(int to = -1, int cap = -1, int rev = -1) {
    this->to = to;
    this->cap = cap;
    this->rev = rev;
  }
};

const int MAX_N = 100;
const int MAX_V = MAX_N * MAX_N + 10;
int level[MAX_V];
int iter[MAX_V];
vector <Edge> G[MAX_V];

void add_edge(int from, int to, int cap) {
  G[from].push_back(Edge(to, cap, G[to].size()));
  G[to].push_back(Edge(from, 0, G[from].size() - 1));
}

void bfs(int s) {
  memset(level, -1, sizeof(level));
  queue<int> que;
  level[s] = 0;
  que.push(s);

  while (!que.empty()) {
    int v = que.front();
    que.pop();

    for (int i = 0; i < (int) G[v].size(); ++i) {
      Edge *e = &G[v][i];

      if (e->cap > 0 && level[e->to] < 0) {
        level[e->to] = level[v] + 1;
        que.push(e->to);
      }
    }
  }
}

int dfs(int v, int t, int f) {
  if (v == t) return f;

  for (int &i = iter[v]; i < (int) G[v].size(); ++i) {
    Edge *e = &G[v][i];

    if (e->cap > 0 && level[v] < level[e->to]) {
      int d = dfs(e->to, t, min(f, e->cap));
      if (d > 0) {
        e->cap -= d;
        G[e->to][e->rev].cap += d;
        return d;
      }
    }
  }

  return 0;
}

int max_flow(int s, int t) {
  int flow = 0;

  for (;;) {
    bfs(s);
    if (level[t] < 0) return flow;
    memset(iter, 0, sizeof(iter));
    int f;
    while ((f = dfs(s, t, INF)) > 0) {
      flow += f;
    }
  }
}

int DY[4] = {-1, 0, 1, 0};
int DX[4] = {0, 1, 0, -1};

int main() {
  int N, M;
  cin >> N >> M;

  string grid[N];
  string row;

  for (int i = 0; i < N; ++i) {
    cin >> row;
    grid[i] = row;
  }

  int s = 0;
  int t = MAX_V - 1;

  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      int u = y * M + x + 1;

      if (grid[y][x] == '#') continue;
      if ((y + x) % 2 != 0) {
        add_edge(u, t, 1);
        continue;
      }

      add_edge(s, u, 1);

      for (int i = 0; i < 4; ++i) {
        int ny = y + DY[i];
        int nx = x + DX[i];

        if (ny < 0 || nx < 0 || N <= ny || M <= nx) continue;
        if (grid[ny][nx] == '#') continue;

        int v = ny * M + nx + 1;

        add_edge(u, v, 1);
      }
    }
  }

  cout << max_flow(s, t) << endl;

  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      if ((y + x) % 2 != 0) continue;
      int u = y * M + x + 1;

      for (Edge edge : G[u]) {
        if (edge.to == 0 || edge.cap != 0) continue;

        int ny = (edge.to - 1) / M;
        int nx = (edge.to - 1) % M;

        if (abs(u - edge.to) < M) {
          if (x < nx) {
            grid[y][x] = '>';
            grid[ny][nx] = '<';
          } else {
            grid[y][x] = '<';
            grid[ny][nx] = '>';
          }
        } else {
          if (y < ny) {
            grid[y][x] = 'v';
            grid[ny][nx] = '^';
          } else {
            grid[y][x] = '^';
            grid[ny][nx] = 'v';
          }
        }
      }
    }
  }

  for (int y = 0; y < N; ++y) {
    cout << grid[y] << endl;
  }

  return 0;
}

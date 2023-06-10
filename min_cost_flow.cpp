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

const int MAX_V = 2503;
const int INF = INT_MAX;

typedef pair<ll, int> P;
int V;

struct Farmer {
  int y;
  int x;

  Farmer(int y = -1, int x = -1) {
    this->y = y;
    this->x = x;
  }
};

struct Point {
  int y;
  int x;

  Point(int y = -1, int x = -1) {
    this->y = y;
    this->x = x;
  }
};

struct Edge {
  int to;
  ll cap;
  ll cost;
  int rev;

  Edge(int to = -1, ll cap = -1, ll cost = -1, int rev = -1) {
    this->to = to;
    this->cap = cap;
    this->cost = cost;
    this->rev = rev;
  }
};

struct Mapping {
  int fid;
  int pid;

  Mapping (int fid = -1, int pid = -1) {
    this->fid = fid;
    this->pid = pid;
  }
};

class MinCostFlow {
public:
  int V;
  ll h[MAX_V];
  int dist[MAX_V];
  int prevv[MAX_V];
  int preve[MAX_V];
  vector <Edge> G[MAX_V];

  MinCostFlow(int V) {
    this->V = V;
  }

  void add_edge(int from, int to, ll cap, ll cost) {
    G[from].push_back(Edge(to, cap, cost, G[to].size()));
    G[to].push_back(Edge(from, 0, -cost, G[from].size() - 1));
  }

  ll min_cost_flow(int s, int t, ll flow_limit) {
    ll f = 0;
    ll totalCost = 0;
    fill(h, h + MAX_V, 0);

    while (f < flow_limit) {
      fprintf(stderr, "f: %lld, limit: %lld\n", f, flow_limit);
      priority_queue<P, vector<P>, greater<P>> pque;
      fill(dist, dist + V, INF);
      dist[s] = 0;
      pque.push(P(0, s));

      while (!pque.empty()) {
        P p = pque.top();
        pque.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;

        for (int i = 0; i < (int) G[v].size(); ++i) {
          Edge *edge = &G[v][i];
          if (edge->cap <= 0) continue;

          ll cost = edge->cost + h[v] - h[edge->to];
          if (dist[edge->to] - dist[v] > cost) {
            dist[edge->to] = dist[v] + cost;
            prevv[edge->to] = v;
            preve[edge->to] = i;
            pque.push(P(dist[edge->to], edge->to));
          }
        }
      }

      if (dist[t] == INF) {
        return -1;
      }

      for (int v = 0; v < V; ++v) {
        h[v] += dist[v];
      }

      ll c = flow_limit - f;
      for (int v = t; v != s; v = prevv[v]) {
        c = min(c, G[prevv[v]][preve[v]].cap);
      }

      f += c;
      totalCost += c * h[t];

      // fprintf(stderr, "h[s]: %d, h[t]: %d, cost: %d, prev_cost: %d\n", h[s], h[t], cost, prev_cost);

      for (int v = t; v != s; v = prevv[v]) {
        Edge *edge = &G[prevv[v]][preve[v]];
        edge->cap -= c;
        G[v][edge->rev].cap += c;
      }
    }

    return totalCost;
  }
};

int main() {
  int N, M;
  cin >> N >> M;
  V = N + M + 2;

  MinCostFlow m(V);

  vector<Farmer> farmers;
  int y, x;
  for (int i = 0; i < N; ++i) {
    cin >> y >> x;
    farmers.push_back(Farmer(y, x));
  }

  vector<Point> points;
  for (int i = 0; i < M; ++i) {
    cin >> y >> x;
    points.push_back(Point(y, x));
  }

  int s = N + M;
  int t = N + M + 1;
  fprintf(stderr, "s: %d, t: %d\n", s, t);

  for (int i = 0; i < N; ++i) {
    m.add_edge(s, i, 1, 0);

    for (int j = 0; j < M; ++j) {
      int cost = abs(farmers[i].y - points[j].y) + abs(farmers[i].x - points[j].x);
      m.add_edge(i, N + j, 1, cost);
    }
  }

  for (int j = 0; j < M; ++j) {
    m.add_edge(N + j, t, 1, 0);
  }

  // auto res = min_cost_flow(s, t, 1);
  auto res = m.min_cost_flow(s, t, min(N, M));
  cout << res << endl;
  vector<Mapping> ret;

  for (int i = 0; i < N; ++i) {
    Farmer farmer = farmers[i];

    for (Edge &edge : m.G[i]) {
      if (edge.to == s) continue;
      if (edge.cap > 0) continue;

      ret.push_back(Mapping(i, edge.to - N));
      Point p = points[edge.to - N];
      fprintf(stderr, "from: %d, to: %d, cap: %lld cost: %lld (%d, %d) -> (%d, %d)\n",
          i, edge.to, edge.cap, edge.cost, farmer.y, farmer.x, p.y, p.x);
    }
  }

  return 0;
}


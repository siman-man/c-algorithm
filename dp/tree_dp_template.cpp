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

const int MAX_N = 100010;
vector <vector<int>> G(MAX_N);
vector<int> V[MAX_N];
int SUM[MAX_N];
map<int, vector<int>> CAND;
int g_minC;

class TreeDP {
public:
  vector <vector<int>> G;

  void add_edge(int from, int to) {
    G[from].push_back(to);
  }

  void dfs() {
  }

  void rdfs() {
  }
};

int dfs(int u, int parent = -1) {
  // fprintf(stderr, "u: %d, p: %d\n", u, parent);
  int cnt = 0;
  int max_c = 0;

  for (int i = 0; i < (int) G[u].size(); ++i) {
    int v = G[u][i];
    if (v == parent) continue;

    int c = dfs(v, u);
    // fprintf(stderr, "p: %d, i: %d, u: %d, v: %d, c: %d\n", parent, i, u, v, c);
    max_c = max(max_c, c);
    cnt += c;
    V[u].push_back(c);
  }

  SUM[u] = cnt;

  return cnt + 1;
}

void rdfs(int u, int parent = -1, int pv = 0) {
  // fprintf(stderr, "u: %d, pv: %d\n", u, pv);
  int acc = SUM[u];
  int idx = 0;
  int max_c = pv;

  for (int i = 0; i < (int) G[u].size(); ++i) {
    int v = G[u][i];
    if (v == parent) continue;

    max_c = max(max_c, V[u][idx]);

    int s = pv + acc - V[u][idx] + 1;
    rdfs(v, u, s);

    idx++;
  }

  // fprintf(stderr, "rdfs: u: %d, max_c: %d\n", u, max_c);
  g_minC = min(g_minC, max_c);
  CAND[max_c].push_back(u);
}

void solver() {
  int N;
  cin >> N;

  g_minC = INT_MAX;
  CAND.clear();
  memset(SUM, -1, sizeof(SUM));

  for (int i = 0; i <= N; ++i) {
    V[i].clear();
    G[i].clear();
  }

  int x, y;
  for (int i = 0; i < N - 1; ++i) {
    cin >> x >> y;

    G[x].push_back(y);
    G[y].push_back(x);
  }

  dfs(1);
  rdfs(1);

  // fprintf(stderr, "minC: %d\n", g_minC);
  vector<int> cands = CAND[g_minC];

  if (cands.size() <= 1) {
    int v = cands[0];
    cout << v << " " << G[v][0] << endl;
    cout << v << " " << G[v][0] << endl;
  } else {
    int u = cands[0];
    int v = cands[1];

    int pv = -1;
    int vl = v;
    while (pv != G[vl][0]) {
      for (int nv : G[vl]) {
        if (nv == u) continue;
        if (nv == pv) continue;

        pv = vl;
        vl = nv;
        break;
      }
    }

    cout << pv << " " << vl << endl;
    cout << u << " " << vl << endl;
  }
}

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; ++i) {
    solver();
  }

  return 0;
}

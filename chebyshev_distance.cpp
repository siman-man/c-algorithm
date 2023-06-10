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

int max_chebyshev_distance(const vector<vector<int>> &P) {
  int k = P[0].size();
  int d = 1 << (k - 1);
  int n = P.size();
  vector<int> max_dist(d, INT_MIN);
  vector<int> min_dist(d, INT_MAX);

  fprintf(stderr, "n: %d, k: %d\n", n, k);

  for (int i = 0; i < n; ++i) {
    vector<int> points = P[i];

    for (int mask = 0; mask < d; ++mask) {
      int v = points[0];

      for (int j = 1; j < k; ++j) {
        if (mask >> (j - 1) & 1) {
          v -= points[j];
        } else {
          v += points[j];
        }
      }

      max_dist[mask] = max(max_dist[mask], v);
      min_dist[mask] = min(min_dist[mask], v);
    }
  }

  int res = INT_MIN;

  for (int i = 0; i < d; ++i) {
    int v = max_dist[i] - min_dist[i];
    res = max(res, v);
  }

  return res;
}

class Solution {
public:
  int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
    int N = arr1.size();
    vector<vector<int>> P;

    for (int i = 0; i < N; ++i) {
      vector<int> points;
      int x = arr1[i];
      int y = arr2[i];

      points.push_back(x);
      points.push_back(y);

      P.push_back(points);
    }

    return max_chebyshev_distance(P);
  }
};

int main() {
  int N;
  cin >> N;
  vector<int> arr1;
  vector<int> arr2;

  int x, y;
  for (int i = 0; i < N; ++i) {
    cin >> x >> y;

    arr1.push_back(x);
    arr2.push_back(y);
  }

  Solution sol;
  cout << sol.maxAbsValExpr(arr1, arr2) << endl;

  return 0;
}

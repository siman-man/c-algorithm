#include <algorithm>
#include <cassert>
#include <cmath>
#include <float.h>
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

struct Point {
  double y;
  double x;

  Point(double y = -1, double x = -1) {
    this->y = y;
    this->x = x;
  }
};

bool compareY(const Point &p1, const Point &p2) {
  return p1.y < p2.y;
}

bool compareX(const Point &p1, const Point &p2) {
  return p1.x < p2.x;
}

// Verified by http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A
double closestPair(Point *points, int n) {
  if (n <= 1) return DBL_MAX;

  int m = n / 2;
  double x = points[m].x;
  double d = min(closestPair(points, m), closestPair(points + m, n - m));
  inplace_merge(points, points + m, points + n, compareY);

  vector <Point> b;
  for (int i = 0; i < n; ++i) {
    if (fabs(points[i].x - x) >= d) continue;

    for (int j = 0; j < b.size(); ++j) {
      double dx = points[i].x - b[b.size() - j - 1].x;
      double dy = points[i].y - b[b.size() - j - 1].y;

      if (dy >= d) break;
      d = min(d, sqrt(dx * dx + dy * dy));
    }
    b.push_back(points[i]);
  }

  return d;
}

int main() {
  int N;
  cin >> N;
  Point points[N];

  double x, y;
  for (int i = 0; i < N; ++i) {
    cin >> x >> y;
    points[i] = Point(y, x);
  }

  sort(points, points + N, compareX);

  cout << fixed << setprecision(10) << closestPair(points, N) << endl;

  return 0;
}

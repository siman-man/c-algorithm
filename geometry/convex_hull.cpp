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

const double EPS = 1e-9;
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

class Point {
public:
  double x;
  double y;

  Point(double x = 0.0, double y = 0.0) {
    this->x = x;
    this->y = y;
  }

  Point operator+(Point p) { return Point(x + p.x, y + p.y); }

  Point operator-(Point p) { return Point(x - p.x, y - p.y); }

  Point operator*(double a) { return Point(a * x, a * y); }

  Point operator/(double a) { return Point(x / a, y / a); }

  double norm() { return x * x + y * y; }

  double abs() { return sqrt(norm()); }

  bool operator<(const Point &p) const {
    return x != p.x ? x < p.x : y < p.y;
  }

  bool operator==(const Point &p) const {
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};

typedef Point Vector;
struct Segment {
  Point p1, p2;
};

typedef Segment Line;

double dot(const Vector &a, const Vector &b) {
  return a.x * b.x + a.y * b.y;
}

double cross(const Vector &a, const Vector &b) {
  return a.x * b.y - a.y * b.x;
}

typedef vector <Point> Polygon;

int ccw(Point p0, Point p1, Point p2) {
  Vector a = p1 - p0;
  Vector b = p2 - p0;
  if (cross(a, b) > EPS) return COUNTER_CLOCKWISE;
  if (cross(a, b) < -EPS) return CLOCKWISE;
  if (dot(a, b) < -EPS) return ONLINE_BACK;
  if (a.norm() < b.norm()) return ONLINE_FRONT;

  return ON_SEGMENT;
}

Polygon andrewScan(Polygon s) {
  Polygon u, l;
  if (s.size() < 3) return s;
  sort(s.begin(), s.end());

  u.push_back(s[0]);
  u.push_back(s[1]);
  l.push_back(s[s.size() - 1]);
  l.push_back(s[s.size() - 2]);

  for (int i = 2; i < s.size(); ++i) {
    for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CLOCKWISE; --n) {
      u.pop_back();
    }
    u.push_back(s[i]);
  }

  for (int i = s.size() - 3; i >= 0; --i) {
    for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; --n) {
      l.pop_back();
    }
    l.push_back(s[i]);
  }

  reverse(l.begin(), l.end());
  for (int i = u.size() - 2; i >= 1; --i) l.push_back(u[i]);

  return l;
}

int main() {
  int Q;
  cin >> Q;

  int x0, x1, x2, x3;
  int y0, y1, y2, y3;

  for (int i = 0; i < Q; ++i) {
    cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    Point p1(x0, y0);
    Point p2(x1, y1);
    Point p3(x2, y2);
    Point p4(x3, y3);
  }

  return 0;
}
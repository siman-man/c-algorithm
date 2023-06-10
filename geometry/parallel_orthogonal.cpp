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

#define equals(a, b) (fabs((a) - (b)) < EPS)

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

class Circle {
public:
  Point c;
  double r;

  Circle(Point c = Point(), double r = 0.0) {
    this->c = c;
    this->r = r;
  }
};

typedef vector <Point> Polygon;

bool isOrthogonal(const Vector &a, const Vector &b) {
  return equals(dot(a, b), 0.0);
}

bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
  return isOrthogonal(a1 - a2, b1 - b2);
}

bool isOrthogonal(Segment s1, Segment s2) {
  return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}

bool isParallel(const Vector &a, const Vector &b) {
  return equals(cross(a, b), 0.0);
}

bool isParallel(Point a1, Point a2, Point b1, Point b2) {
  return isParallel(a1 - a2, b1 - b2);
}

bool isParallel(Segment s1, Segment s2) {
  return equals(cross(s1.p2 - s2.p1, s2.p2 - s2.p1), 0.0);
}

// 直線の直行・平行判定
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

    if (isOrthogonal(p1, p2, p3, p4)) {
      cout << 1 << endl;
    } else if (isParallel(p1, p2, p3, p4)) {
      cout << 2 << endl;
    } else {
      cout << 0 << endl;
    }
  }
  return 0;
}
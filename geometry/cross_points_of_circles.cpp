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

  double arg() { return atan2(y, x); }

  bool operator<(const Point &p) const {
    return x != p.x ? x < p.x : y < p.y;
  }

  bool operator==(const Point &p) const {
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};

typedef Point Vector;

class Circle {
public:
  Point c;
  double r;

  Circle(Point c = Point(), double r = 0.0) {
    this->c = c;
    this->r = r;
  }

  pair <Point, Point> getCrossPoints(Circle c2) {
    double d = (c - c2.c).abs();
    double a = acos((r * r + d * d - c2.r * c2.r) / (2 * r * d));
    double t = (c2.c - c).arg();

    return make_pair(c + polar(r, t + a), c + polar(r, t - a));
  }

private:

  Vector polar(double a, double r) {
    return Point(cos(r) * a, sin(r) * a);
  }
};

double getDistance(Point a, Point b) {
  return (a - b).abs();
}

bool intersect(Circle c1, Circle c2) {
  return abs(c1.r - c2.r) <= getDistance(c1.c, c2.c) && getDistance(c1.c, c2.c) < c1.r + c2.r + EPS;
}

// 円と円の交点
int main() {
  int c1x, c1y, c1r;
  int c2x, c2y, c2r;

  cin >> c1x >> c1y >> c1r;
  cin >> c2x >> c2y >> c2r;

  Circle c1(Point(c1x, c1y), c1r);
  Circle c2(Point(c2x, c2y), c2r);

  pair <Point, Point> res = c1.getCrossPoints(c2);

  Point p3 = res.first;
  Point p4 = res.second;

  if (p3.x < p4.x) {
    cout << fixed << setprecision(10) << p3.x << " " << p3.y << " " << p4.x << " " << p4.y << endl;
  } else if (p3.x == p4.x) {
    if (p3.y < p4.y) {
      cout << fixed << setprecision(10) << p3.x << " " << p3.y << " " << p4.x << " " << p4.y << endl;
    } else {
      cout << fixed << setprecision(10) << p4.x << " " << p4.y << " " << p3.x << " " << p3.y << endl;
    }
  } else {
    cout << fixed << setprecision(10) << p4.x << " " << p4.y << " " << p3.x << " " << p3.y << endl;
  }

  return 0;
}
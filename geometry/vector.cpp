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

  double arg() { return atan2(y, x); }

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

  Segment(Point p1 = Point(), Point p2 = Point()) {
    this->p1 = p1;
    this->p2 = p2;
  }
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

Point project(Segment s, Point p) {
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / base.norm();
  return s.p1 + base * r;
}

Point reflect(Segment s, Point p) {
  return p + (project(s, p) - p) * 2.0;
}

double getDistance(Point a, Point b) {
  return (a - b).abs();
}

double getDistanceLP(Line l, Point p) {
  return fabs(cross(l.p2 - l.p1, p - l.p1) / (l.p2 - l.p1).abs());
}

double getDistanceSP(Segment s, Point p) {
  if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return (p - s.p1).abs();
  if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return (p - s.p2).abs();

  return getDistanceLP(s, p);
}

int ccw(Point p0, Point p1, Point p2) {
  Vector a = p1 - p0;
  Vector b = p2 - p0;
  if (cross(a, b) > EPS) return COUNTER_CLOCKWISE;
  if (cross(a, b) < -EPS) return CLOCKWISE;
  if (dot(a, b) < -EPS) return ONLINE_BACK;
  if (a.norm() < b.norm()) return ONLINE_FRONT;

  return ON_SEGMENT;
}

bool intersect(Point p1, Point p2, Point p3, Point p4) {
  return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 && ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}

bool intersect(Segment s1, Segment s2) {
  return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

bool intersect(Circle c, Line l) {
  return getDistanceLP(l, c.c) < c.r + EPS;
}

bool intersect(Circle c1, Circle c2) {
  return abs(c1.r - c2.r) <= getDistance(c1.c, c2.c) && getDistance(c1.c, c2.c) < c1.r + c2.r + EPS;
}

double getDistance(Segment s1, Segment s2) {
  if (intersect(s1, s2)) return 0.0;
  return min(
    min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
    min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2))
  );
}

Point getCrossPoint(Segment s1, Segment s2) {
  Vector base = s2.p2 - s2.p1;
  double d1 = abs(cross(base, s1.p1 - s2.p1));
  double d2 = abs(cross(base, s1.p2 - s2.p1));
  double t = d1 / (d1 + d2);

  return s1.p1 + (s1.p2 - s1.p1) * t;
}

pair <Point, Point> getCrossPoints(Circle c, Line l) {
  assert(intersect(c, l));
  Vector pr = project(l, c.c);
  Vector e = (l.p2 - l.p1) / (l.p2 - l.p1).abs();
  double base = sqrt(c.r * c.r - (pr - c.c).norm());

  return make_pair(pr + e * base, pr - e * base);
}

double arg(Vector p) {
  return atan2(p.y, p.x);
}

Vector polar(double a, double r) {
  return Point(cos(r) * a, sin(r) * a);
}

int main() {
  return 0;
}
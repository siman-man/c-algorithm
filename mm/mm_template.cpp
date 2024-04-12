#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <climits>
#include <map>
#include <queue>
#include <set>
#include <cstring>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
typedef long long ll;

class Xorshift {
public:
  Xorshift(uint64_t seed = 88675123) {
    _x = 123456789;
    _y = 362436069;
    _z = 521288629;
    _w = seed;

    for (int i = 0; i < 100; ++i) {
      next();
    }
  }

  uint64_t next(uint64_t a, uint64_t b) {
    return a + (next() % (b - a + 1));
  }

  uint64_t next() {
    uint64_t t = _x ^ (_x << 11);
    _x = _y;
    _y = _z;
    _z = _w;
    _w = (_w ^ (_w >> 19)) ^ (t ^ (t >> 8));
    return _w;
  }

  double random_double() {
    return static_cast<double>(next()) / UINT64_MAX;
  }

  double random_double(double a, double b) {
    return a + (b - a) * random_double();
  }

private:
  uint64_t _x, _y, _z, _w;
};

Xorshift g_rng;

class Timer {
public:
  Timer() {
    begin();
    _duration = 0.0;
  }

  void begin() {
    _start_at = chrono::system_clock::now();
  }

  double get_time() {
    chrono::system_clock::time_point end_at = chrono::system_clock::now();
    _duration = chrono::duration_cast<std::chrono::nanoseconds>(end_at - _start_at).count();
    return _duration / 1000000000.0;
  }

  double progress(double time_limit) {
    return get_time() / time_limit;
  }

private:
  chrono::system_clock::time_point _start_at;
  double _duration;
};

Timer g_timer;

class Solver {
public:
  void run() {
    load_data();
    setup();
  }

private:
  void load_data() {
  }

  void setup() {
  }
};

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  Solver solver;
  solver.run();

  return 0;
}

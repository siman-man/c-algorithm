#include <iostream>

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

int main() {
  Xorshift rng;
  for (int i = 0; i < 20; ++i) {
    std::cout << rng.random_double(2.0, 8.0) << std::endl;
  }
  return 0;
}

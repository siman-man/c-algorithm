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

class Rational {
public:
  int a;
  int b;

  Rational(int a, int b) {
    int g = gcd(a, b);

    if (g != 0) {
      this->a = a / g;
      this->b = b / g;
    } else {
      this->a = a;
      this->b = b;
    }
  }

private:
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }
};

int main() {
  Rational r(10, 2);

  return 0;
}
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

int main() {
  vector<int> A;

  A.push_back(1);
  A.push_back(2);
  A.push_back(2);
  A.push_back(10);

  auto it = lower_bound(A.begin(), A.end(), 11);

  if (it == A.end()) {
    cout << "Not found" << endl;
  } else {
    cout << *it << endl;
    cout << it - A.begin() << endl;
  }

  return 0;
}
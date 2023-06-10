#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> V;

  V.push_back(1);
  V.push_back(20);
  V.push_back(100);
  V.push_back(83);
  V.push_back(12);

  // erase at idx
  V.erase(V.begin() + 4);

  // erase last element
  V.erase(V.end() - 1);

  // accessing last element
  fprintf(stderr, "Last element = %d\n", V.back());

  // modify last element
  V.back() = 123;
  fprintf(stderr, "Last element = %d\n", V.back());

  for (int v : V) {
    cout << v << endl;
  }

  return 0;
}
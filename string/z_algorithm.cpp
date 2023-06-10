#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <map>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;
typedef long long ll;

vector<int> z_algorithm(string S) {
  int N = S.size();
  vector<int> ret(N);
  ret[0] = N;

  int i = 1;
  int j = 0;

  while (i < N) {
    while (i + j < N && S[j] == S[i + j]) ++j;

    ret[i] = j;

    if (j == 0) {
      ++i;
      continue;
    }

    int k = 1;

    while (i + j < N && k + ret[k] < j) {
      ret[i + k] = ret[k];
      ++k;
    }

    i += k;
    j -= k;
  }

  return ret;
}

int main() {
  string S;
  cin >> S;

  vector<int> ret = z_algorithm(S);

  for (int i = 0; i < ret.size(); ++i) {
    cout << ret[i];

    if (i != ret.size() - 1) {
      cout << " ";
    }
  }

  cout << endl;

  return 0;
}
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

const int MAX_N = 500'000;

int n, k;
int _rank[MAX_N + 1];
int tmp[MAX_N + 1];

bool compare_sa(int i, int j) {
  if (_rank[i] != _rank[j]) {
    return _rank[i] < _rank[j];
  } else {
    int ri = i + k <= n ? _rank[i + k] : -1;
    int rj = j + k <= n ? _rank[j + k] : -1;

    return ri < rj;
  }
}

void construct_sa(string S, int *sa) {
  n = S.size();

  for (int i = 0; i <= n; ++i) {
    sa[i] = i;
    _rank[i] = i < n ? S[i] : -1;
  }

  for (k = 1; k <= n; k *= 2) {
    sort(sa, sa + n + 1, compare_sa);

    tmp[sa[0]] = 0;
    for (int i = 1; i <= n; ++i) {
      tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
    }
    for (int i = 0; i <= n; ++i) {
      _rank[i] = tmp[i];
    }
  }
}

void construct_lcp(string S, int *sa, int *lcp) {
  int n = S.size();
  for (int i = 0; i <= n; ++i) {
    _rank[sa[i]] = i;
  }

  int h = 0;
  lcp[0] = 0;
  for (int i = 0; i < n; ++i) {
    int j = sa[_rank[i] - 1];

    if (h > 0) --h;
    for (; j + h < n && i + h < n; ++h) {
      if (S[j + h] != S[i + h]) break;
    }

    lcp[_rank[i] - 1] = h;
  }
}

int main() {
  string S;
  cin >> S;
  int N = S.size();
  int sa[N + 1];

  construct_sa(S, sa);

  for (int i = 1; i <= n; ++i) {
    cout << sa[i];

    if (i == n) {
      cout << endl;
    } else {
      cout << " ";
    }
  }

  return 0;
}
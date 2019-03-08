#include <algorithm>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;
typedef long long ll;

const int MAX_K = 1000;

int n, k, m;
int grid[2 * MAX_K + 1][2 * MAX_K + 1];

int grid_count(int y, int x) {
  int cnt = 0;
  int ym = (y + k) % m;
  int xm = (x + k) % m;

  if (y + k <= m && x + k <= m) {
    cnt += grid[y + k][x + k] - grid[y + k][x] - grid[y][x + k] + grid[y][x];
  }

  if (y + k <= m && x + k > m) {
    cnt += grid[y + k][m] - grid[y + k][x] - grid[y][m] + grid[y][x];
    cnt += grid[y + k][xm] - grid[y + k][0] - grid[y][xm] + grid[y][0];
  }

  if (y + k > m && x + k <= m) {
    cnt += grid[m][x + k] - grid[m][x] - grid[y][x + k] + grid[y][x];
    cnt += grid[ym][x + k] - grid[ym][x] - grid[0][x + k] + grid[0][x];
  }

  if (y + k > m && x + k > m) {
    cnt += grid[m][m] - grid[m][x] - grid[y][m] + grid[y][x];
    cnt += grid[ym][xm] - grid[ym][0] - grid[0][xm] + grid[0][0];
    cnt += grid[ym][m] - grid[ym][x] - grid[0][m] + grid[0][x];
    cnt += grid[m][xm] - grid[y][0] - grid[y][xm] + grid[y][0];
  }

  return cnt;
}

int main() {
  cin >> n >> k;
  memset(grid, 0, sizeof(grid));
  m = 2 * k;

  char c;
  int x, y;
  for (int i = 0; i < n; i++) {
    cin >> x >> y >> c;

    x++;
    y++;

    if (c == 'W') {
      y += k;
    }

    grid[y % m + 1][x % m + 1]++;
  }

  for (int y = 1; y <= m; y++) {
    for (int x = 1; x <= m; x++) {
      grid[y][x] += grid[y][x - 1];
    }
  }

  for (int x = 1; x <= m; x++) {
    for (int y = 1; y <= m; y++) {
      grid[y][x] += grid[y - 1][x];
    }
  }

  int ans = 0;

  for (int y = 0; y < m; y++) {
    for (int x = 0; x < m; x++) {
      int oy = (y + k) % m;
      int ox = (x + k) % m;

      int cnt = grid_count(y, x) + grid_count(oy, ox);

      ans = max(ans, cnt);
    }
  }

  cout << ans << endl;

  return 0;
}

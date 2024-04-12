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

using namespace std;
typedef long long ll;

const ll CYCLE_PER_SEC = 2700000000;
double TIME_LIMIT = 2.0;

unsigned long long xor128() {
  static unsigned long long rx = 123456789, ry = 362436069, rz = 521288629, rw = 88675123;
  unsigned long long rt = (rx ^ (rx << 11));
  rx = ry;
  ry = rz;
  rz = rw;
  return (rw = (rw ^ (rw >> 19)) ^ (rt ^ (rt >> 8)));
}

unsigned long long int get_cycle() {
  unsigned int low, high;
  __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
  return ((unsigned long long int) low) | ((unsigned long long int) high << 32);
}

double get_time(unsigned long long int begin_cycle) {
  return (double) (get_cycle() - begin_cycle) / CYCLE_PER_SEC;
}

int calc_score_full() {
  int score = 0;

  return score;
}

void sa(double time_limit = TIME_LIMIT) {
  int cur_score = calc_score_full();
  int best_score = cur_score;

  double cur_time = g_timer.get_time();
  double total_diff = 0.0;
  double t = 0.1;
  ll R = 100000000;
  int try_count = 0;

  while (cur_time < time_limit) {
    cur_time = g_timer.get_time();
    double remain_time = (time_limit - cur_time) / time_limit;

    int score = calc_score_full();
    double diff_score = score - cur_score;
    total_diff += fabs(diff_score);

    if (diff_score > 0 || (g_rng.next() % R < R * exp(diff_score / (t * pow(remain_time, 2))))) {
      cur_score = score;

      if (best_score < score) {
        best_score = score;
      }
    } else {
    }

    ++try_count;
    double average_diff = total_diff / try_count;
    t = 0.25 * remain_time * average_diff;
  }
}

int main() {
}

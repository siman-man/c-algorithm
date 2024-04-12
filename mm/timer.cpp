#include <iostream>
#include <chrono>

using namespace std;

class CycleTimer {
public:
  CycleTimer() {
    begin();
  }

  double get_time() {
    return (double) (get_cycle() - _begin_cycle) / CYCLE_PER_SEC;
  }

  void begin() {
    _begin_cycle = get_cycle();
  }

private:
  const uint64_t CYCLE_PER_SEC = 2700000000;
  uint64_t _begin_cycle;

  uint64_t get_cycle() {
    uint64_t low, high;
    __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
    return low | (high << 32);
  }
};

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

int main() {
  CycleTimer timer;
  uint64_t loop_cnt = 0;

  while (timer.get_time() < 1.0) {
    ++loop_cnt;
  }

  cout << loop_cnt << endl;
}

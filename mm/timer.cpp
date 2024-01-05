#include <iostream>
#include <chrono>

using namespace std;

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
  Timer timer;
  uint64_t loop_cnt = 0;

  while (timer.get_time() < 1.0) {
    ++loop_cnt;
  }

  cout << loop_cnt << endl;
}
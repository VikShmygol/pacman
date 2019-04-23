#pragma once
#include <chrono>
using namespace std::chrono;

struct DelayTimer {
  steady_clock::time_point cycle_start_time = steady_clock::now();
};

class DelayOffTimer {
 public:
  void Start();
  bool Check(milliseconds delay_off);

 private:
  DelayTimer timer_;
};

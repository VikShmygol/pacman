#pragma once
#include <chrono>
using namespace std::chrono;

struct Timer {
  steady_clock::time_point cycle_start_time = steady_clock::now();
};

class OnOffTimer {
 public:
  OnOffTimer();
  bool Activate(milliseconds time_on, milliseconds time_off);

private:
  Timer timer_;
};


#include "pch.h"
#include "delay_off_timer_class.h"


void DelayOffTimer::Start() {
	   timer_.cycle_start_time = steady_clock::now();
}

bool DelayOffTimer::Check(milliseconds delay_off) {
  milliseconds duration = duration_cast<milliseconds>(steady_clock::now() -
                                                      timer_.cycle_start_time);
  return duration < delay_off;
}
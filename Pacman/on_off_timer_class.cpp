#include "pch.h"
#include "on_off_timer_class.h"

OnOffTimer::OnOffTimer(){};

bool OnOffTimer::Activate(milliseconds time_on, milliseconds time_off) {
  milliseconds duration = duration_cast<milliseconds>(steady_clock::now() -
                                                      timer_.cycle_start_time);

  if (duration > (time_on + time_off)) {
    timer_.cycle_start_time = steady_clock::now();
  }

  return duration < time_on;
}



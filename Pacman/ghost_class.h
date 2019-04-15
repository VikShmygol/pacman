#pragma once
#include <string>
#include <vector>
#include <map>
#include "on_off_timer_class.h"

using namespace std;

struct GhostData {
  bool locked;
  bool blinking;
  bool first_move;
  OnOffTimer timer_to_blink;
  wchar_t substitute_symbol;
  int location_row;
  int location_col;
  int direction;
  int resurrection_row;
  int resurrection_col;
};

class Ghost {
 public:
  Ghost(int location_row, int location_col);

  void GhostAction(vector<wstring>& level_map);

 private:
  GhostData ghost_;

// This method returns a direction to move for ghost
// The input is a map of neighbours for each direction
// and direction that must be skipped (only if direction_to_avoid != 5)
  int GhostMoveDirection(const map<int, wchar_t>&);
};

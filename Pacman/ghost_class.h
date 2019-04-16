#pragma once
#include <map>
#include "dynamic_obj_class.h"
#include "on_off_timer_class.h"

using namespace std;

struct GhostData {
  bool locked;
  bool blinking;
  bool first_move;
  OnOffTimer timer_to_blink;
  wchar_t substitute_symbol;
  const int resurrection_row;
  const int resurrection_col;
};

class Ghost : public DynamicObj {
 public:
  Ghost(int location_row, int location_col);

  void Action(vector<wstring>& level_map) override;

 private:
  GhostData ghost_;

// This method returns a direction to move for ghost
// The input is a map of neighbours for each direction
// and direction that must be skipped (only if direction_to_avoid != 5)
  int GhostMoveDirection(const map<int, wchar_t>&);
};

#pragma once
#include <map>
#include "object_class.h"
#include "on_off_timer_class.h"

using namespace std;

struct GhostData {
  bool locked;
  bool is_scared;
  bool first_move;
  int direction;
  const int resurrection_row;
  const int resurrection_col;
  wchar_t substitute_symbol;
  OnOffTimer timer_to_blink;
};

class Ghost : public DynObject {
 public:
  Ghost(int location_row, int location_col);

  void Action(vector<wstring>& level_map) override;
  void set_to_scared();
  void reset_scared();
  bool get_is_scared() const;
  void Resurrection(vector<wstring>& map);

 private:
  GhostData ghost_;

/* This method returns a direction to move for ghost
   The input is a map of neighbours for each direction
   and direction that must be skipped (only if direction_to_avoid != 5) */
  int GhostMoveDirection(const map<int, wchar_t>&);
};

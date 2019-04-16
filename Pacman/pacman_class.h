#pragma once
#include "object_class.h"

struct PacmanData {
  wchar_t pacman_look;
  bool is_alive = true;
};

class Pacman : public Object {
 public:
 
  Pacman(int location_row, int location_col);

  void Action(vector<wstring>& level_map) override;

  private:
  PacmanData pacman_;
};



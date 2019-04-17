#pragma once
#include "object_class.h"

struct PacmanData {
  int lives;
  int score;

  wchar_t pacman_look;

};

class Pacman : public DynObject {
 public:
 
  Pacman(int location_row, int location_col);

  void Action(vector<wstring>& level_map) override;

  private:
  PacmanData pacman_;
};



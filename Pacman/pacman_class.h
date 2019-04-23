#pragma once
#include "object_class.h"

struct PacmanData {
  wchar_t pacman_look;
  
};

class Pacman : public DynObject {
 public:
 
  Pacman(int location_row, int location_col);

 Collision Action(vector<wstring>& level_map) override;
  void Ressurection(vector<wstring>& map);

  private:
  PacmanData pacman_;
  // vector<Ghost>& ghosts;
};



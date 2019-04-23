#pragma once
#include <vector>
#include "collision_class.h"

using namespace std;

struct DynObjData {
  int location_row;
  int location_col;
  const int resurrection_row;
  const int resurrection_col;
  const string type;
};

/* Base class for all dynamic objects on the map
   such as Pacman and Ghosts */
class DynObject {
 public:
  DynObject(const string obj_type, int row, int col);
  virtual Collision Action(vector<wstring>& map) = 0;
  void set_location_row(int row);
  void set_location_col(int col);
  void set_to_ressurection_row();
  void set_to_ressurection_col();
  int get_location_row() const;
  int get_location_col() const;
  string get_obj_type() const;

 private:
  DynObjData obj_;
};

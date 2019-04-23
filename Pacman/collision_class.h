#pragma once
#include <vector>

using namespace std;

class GameSys;
class Ghost;
class DynObject;

struct CollisionData {
  DynObject* obj_ptr;
  int counter_obj_location_row;
  int counter_obj_location_col;
  wchar_t counter_obj_look;
};

/* Class to handle interaction
   between objects on the map */
class Collision {
 public:
  Collision(DynObject* obj, int counter_obj_location_row,
            int counter_obj_location_col, wchar_t obj_look);

  void Processing(GameSys* level, vector<wstring>& map, vector<Ghost>& ghosts);
  

  private:
  CollisionData collision_;
   int FindGhost(int row, int col, vector<Ghost>& ghosts);
  void HandleGhostPacmanCase(GameSys* game, vector<Ghost>& ghosts,
                              int location_row,
                              int location_col, vector<wstring>& map);
};

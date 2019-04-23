#include "pch.h"
#include "collision_class.h"
#include "constants.h"
#include "game_sys_class.h"
#include <exception>

Collision::Collision(DynObject* obj_ptr, int counter_obj_location_row,
                     int counter_obj_location_col, wchar_t counter_obj_look)
    : collision_{obj_ptr, counter_obj_location_row, counter_obj_location_col, counter_obj_look} {}

void Collision::Processing(GameSys* game, vector<wstring>& map,
                           vector<Ghost>& ghosts) {

	if (collision_.counter_obj_location_col == 0 ||
      collision_.counter_obj_location_row == 0) {
    return;
	}

  if (collision_.obj_ptr->get_obj_type() == "pacman") {
    switch (collision_.counter_obj_look) {
      case kGhostLookScared:
      case kGhostLook:
        HandleGhostPacmanCase(game, ghosts,
                              collision_.counter_obj_location_row,
                              collision_.counter_obj_location_col, map);
        break;
      case kRegularDotLook:
        game->decrement_num_dots();
        game->update_score(10);
        break;
      case kSuperDotLook:
        game->decrement_num_dots();
        game->update_score(100);
        game->ScareGhosts();
        break;
    }
  } else if (collision_.obj_ptr->get_obj_type() == "ghost") {
    int location_row = collision_.obj_ptr->get_location_row();
    int location_col = collision_.obj_ptr->get_location_col();
    HandleGhostPacmanCase(game, ghosts, location_row,
                          location_col, map);
  }
}

int Collision::FindGhost(int row, int col, vector<Ghost>& ghosts) {
  for (int i = 0; i < ghosts.size(); ++i) {
    if (ghosts[i].get_location_row() == row &&
        ghosts[i].get_location_col() == col) {
      return i;
    }
  }
  throw invalid_argument("Ghost's location (row = " + to_string(row) +
                         ", col = " + to_string(col) + ") not found");
}

void Collision::HandleGhostPacmanCase(GameSys* game, vector<Ghost>& ghosts,
                                      int location_row, int location_col,
                                      vector<wstring>& map) {
  int ghost_index = FindGhost(location_row, location_col, ghosts);
  if (ghosts[ghost_index].get_is_scared()) {
    ghosts[ghost_index].Resurrection(map);
    game->update_score(200);
  } else {
    game->StartOverLevel(map);
  }
}
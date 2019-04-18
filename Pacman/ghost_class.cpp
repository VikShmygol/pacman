#include "pch.h"
#include "ghost_class.h"
#include <random>
#include "common_functions.h"
#include "constants.h"


Ghost::Ghost(int row, int col)
    : DynObject("ghost", row, col), ghost_{false, false,       true,
                                                     0,     row,         col,
                                                     '.',   OnOffTimer()} {}

Collision Ghost::Action(vector<wstring>& level_map) {
  int curr_location_row = get_location_row();
  int curr_location_col = get_location_col();

  const wchar_t north_neighbour =
      level_map[curr_location_row - 1][curr_location_col];
  const wchar_t east_neighbour =
      level_map[curr_location_row][curr_location_col + 1];
  const wchar_t south_neighbour =
      level_map[curr_location_row + 1][curr_location_col];
  const wchar_t west_neighbour =
      level_map[curr_location_row][curr_location_col - 1];

  // quiting in case if ghost is surrounded by other ghosts or by walls
  if (!FindCharacter(kGhostPlaceToMove, north_neighbour) &&
      !FindCharacter(kGhostPlaceToMove, east_neighbour) &&
      !FindCharacter(kGhostPlaceToMove, west_neighbour) &&
      !FindCharacter(kGhostPlaceToMove, south_neighbour)) {
    return Collision(this, 0, 0, L' ');
  }

  const map<int, wchar_t> direction_neighbours_map{{0, north_neighbour},
                                                   {1, east_neighbour},
                                                   {2, south_neighbour},
                                                   {3, west_neighbour}};

  ghost_.direction = GhostMoveDirection(direction_neighbours_map);

  if (!ghost_.first_move) {
    level_map[curr_location_row][curr_location_col] = ghost_.substitute_symbol;
  } else {
    level_map[curr_location_row][curr_location_col] = L' ';
    ghost_.first_move = false;
  }

  ghost_.substitute_symbol = direction_neighbours_map.at(ghost_.direction);

  // ghost_.blinking = true;
  wchar_t GhostLook = kGhostLook;

  if (ghost_.is_scared && !ghost_.timer_to_blink.Activate(200ms, 200ms)) {
    GhostLook = ghost_.substitute_symbol;
  }

  switch (ghost_.direction) {
    case 0:
      level_map[--curr_location_row][curr_location_col] = GhostLook;
      set_location_row(curr_location_row);
      break;
    case 1:
      level_map[curr_location_row][++curr_location_col] = GhostLook;
      set_location_col(curr_location_col);
      break;
    case 2:
      level_map[++curr_location_row][curr_location_col] = GhostLook;
      set_location_row(curr_location_row);
      break;
    case 3:
      level_map[curr_location_row][--curr_location_col] = GhostLook;
      set_location_col(curr_location_col);
      break;
  }
  return Collision(this, 0, 0, L' ');
}
void Ghost::set_to_scared() { ghost_.is_scared = true; }
bool Ghost::get_is_scared() const { return ghost_.is_scared; }
void Ghost::reset_scared() { ghost_.is_scared = false; }
void Ghost::Resurrection(vector<wstring>& map) {
  map[get_location_row()][get_location_col()] = ghost_.substitute_symbol;
  map[ghost_.resurrection_row][ghost_.resurrection_col] = kGhostLook;
  set_location_row(ghost_.resurrection_row);
  set_location_col(ghost_.resurrection_col);
  ghost_.is_scared = false;
}

int Ghost::GhostMoveDirection(const map<int, wchar_t>& neighbours_map) {
  const int side_direction_1 = (ghost_.direction + 1) % 4;
  const int side_direction_2 = (ghost_.direction + 3) % 4;
  const int opposite_direction = (ghost_.direction + 2) % 4;
  int direction_to_avoid = opposite_direction;

  if (!FindCharacter(kGhostPlaceToMove, neighbours_map.at(side_direction_1)) &&
      !FindCharacter(kGhostPlaceToMove, neighbours_map.at(side_direction_2)) &&
      !FindCharacter(kGhostPlaceToMove, neighbours_map.at(ghost_.direction))) {
    return opposite_direction;
  } else if (!FindCharacter(kGhostPlaceToMove,
                            neighbours_map.at(side_direction_1)) &&
             !FindCharacter(kGhostPlaceToMove,
                            neighbours_map.at(side_direction_2)) &&
             FindCharacter(kGhostPlaceToMove,
                           neighbours_map.at(ghost_.direction))) {
    return ghost_.direction;
  } else if (!FindCharacter(kGhostPlaceToMove,
                            neighbours_map.at(ghost_.direction))) {
    // direction_to_avoid = ghost_.direction;
  }

  random_device random_seed;
  default_random_engine random_generator(random_seed());
  uniform_int_distribution<int> moving_direction(0, 3);

  int direction;

  while (true) {
    direction = moving_direction(random_generator);
    if ((direction != direction_to_avoid) &&
        FindCharacter(kGhostPlaceToMove, neighbours_map.at(direction))) {
      break;
    }
  }
  return direction;
}
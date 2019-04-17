#include "pch.h"
#include "pacman_class.h"
#include <map>
#include "conio.h"
#include "constants.h"
#include "common_functions.h"


Pacman::Pacman(int row, int col)
    : DynObject("pacman", row, col), pacman_{3, 0, 'v'} {}

void Pacman::Action(vector<wstring>& level_map) {
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

  const map<char, wchar_t> direction_neighbours_map{{'w', north_neighbour},
                                                 {'d', east_neighbour},
                                                 {'s', south_neighbour},
                                                 {'a', west_neighbour}};

  const map<char, pair<int, int>> neighbours_coordinates{
      {'w', make_pair(curr_location_row - 1, curr_location_col)},
      {'d', make_pair(curr_location_row, curr_location_col + 1)},
      {'s', make_pair(curr_location_row + 1, curr_location_col)},
      {'a', make_pair(curr_location_row, curr_location_col - 1)}};

  bool is_moved = false;
  char input = 'e';

  if (_kbhit()) {
    input = _getch();
  }

  if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
    is_moved =
        FindCharacter(kPacmanPlaceToMove, direction_neighbours_map.at(input));
  }

  if (is_moved) {
    level_map[curr_location_row][curr_location_col] = ' ';
    switch (input) {
      case 'w':
        level_map[--curr_location_row][curr_location_col] = kPacmanLook[0];
        set_location_row(curr_location_row);
        break;
      case 'd': 
        level_map[curr_location_row][++curr_location_col] = kPacmanLook[1];
        set_location_col(curr_location_col);
        break;
      case 's': 
        level_map[++curr_location_row][curr_location_col] = kPacmanLook[2];
        set_location_row(curr_location_row);
        break;
      case 'a': 
        level_map[curr_location_row][--curr_location_col] = kPacmanLook[3];
        set_location_col(curr_location_col);
        break;
    }
  }
  return;
}


#include "pch.h"
#include "game_sys_class.h"
#include <Windows.h>
#include <chrono>
#include <codecvt>
#include <iostream>
#include <locale>
#include <thread>
#include "level_class.h"

void GameSys::GameProcessing(const vector<string>& level_filename_vector,
                             vector<wstring>& map) {

  size_t map_height;
  size_t map_width;

  while (true) {
    if (!game_.level.get_num_dots() && game_.level.get_pacman_lives() &&
        game_.current_level < level_filename_vector.size()) {
      game_.level.LoadLevel(level_filename_vector[game_.current_level], map);
      game_.current_level++;
      map_height = game_.level.get_map_height();
      map_width = game_.level.get_map_width();
    } else if (!game_.level.get_num_dots()) {
      cout << "You won, congratulations!" << endl;
      system("PAUSE");
      break;
    } else if (!game_.level.get_pacman_lives()) {
      cout << "Try again!" << endl;
      system("PAUSE");
      game_.level.LoadLevel(level_filename_vector[game_.current_level], map);
    } else {
      game_.level.ProcessingLevel(map);
    }

    ScreenUpdate(map, map_height, map_width);
   
  }
}

void GameSys::ScreenUpdate(vector<wstring>& map, size_t map_height, size_t map_width) {
  ShowConsoleCursor(false);
  for (int i = 0; i < map_height; ++i) {
    for (int j = 0; j < map_width; ++j) {
      SetCursorPosition(i, j);
      wcout << map[i][j];
    }
  }
  cout.flush();
  game_.previous_map = map;
}
    
// The origin (0,0) is top-left.
void GameSys::SetCursorPosition(int row, int col) {
  static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  cout.flush();
  COORD coord = {(SHORT)col, (SHORT)row};
  SetConsoleCursorPosition(hOut, coord);
}

void GameSys::ShowConsoleCursor(bool show_flag) {
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO cursor_info;

  GetConsoleCursorInfo(out, &cursor_info);
  cursor_info.bVisible = show_flag;  // set the cursor visibility
  SetConsoleCursorInfo(out, &cursor_info);
}
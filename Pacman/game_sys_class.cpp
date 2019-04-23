#include "pch.h"
#include "game_sys_class.h"
#include <Windows.h>
#include <chrono>
#include <codecvt>
#include <iostream>
#include <locale>
#include <thread>
#include <fstream>
#include "common_functions.h"
#include "constants.h"
#include <iostream>

void GameSys::GameProcessing(const vector<string>& level_filename_vector,
                             vector<wstring>& map) {

  while (true) {
    if (!level_.num_dots && level_.pacman_lives &&
        game_.current_level < level_filename_vector.size()) {
      LoadLevel(level_filename_vector[game_.current_level], map);
      game_.current_level++;
    } else if (!level_.num_dots) {
      cout << "You won, congratulations!" << endl;
      system("PAUSE");
      break;
    } else if (!level_.pacman_lives) {
      cout << "Try again!" << endl;
      system("PAUSE");
    } else {
      ProcessingLevel(map);
    }

    ScreenUpdate(map, level_.map_height, level_.map_width);
   
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
  cout << endl;
  cout << " Score: " << level_.score
       << "	Lives: " << level_.pacman_lives
	  << endl;
  cout << "Level " << game_.current_level << endl;
  cout << level_.num_dots << endl;
  wcout.flush();
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

void GameSys::LoadLevel(const string& level_filename,
                      vector<wstring>& level_map) {
  level_map.clear();
  level_.ghosts.clear();
  level_.pacman.clear();

  /* Extracting the map data from Unicode file
     into the vector of <wstring> */
  wstring line;
  locale::global(std::locale("fr_FR.UTF-8"));
  const locale empty_locale = std::locale::empty();
  typedef codecvt_utf8_utf16<wchar_t> converter_type;
  const converter_type* converter = new converter_type;
  const locale utf8_locale = std::locale(empty_locale, converter);
  wifstream stream(level_filename);
  stream.imbue(utf8_locale);

  if (stream.fail()) {
    throw invalid_argument("File '" + level_filename + "'" + "failed to open");
  }

  stream >> level_.map_height >> level_.map_width;
  getline(stream, line);
  while (getline(stream, line)) {
    level_map.push_back(line);
  }

  // Counting ghosts and dots
  for (int i = 0; i < level_.map_height; ++i) {
    if (level_map[i].size() < level_.map_width) {
      throw out_of_range("Row " + to_string(i) + " has incorrect width");
    }
    for (int j = 0; j < level_.map_width; ++j) {
      switch (level_map[i][j]) {
        case kSuperDotLook:
        case kRegularDotLook:
          level_.num_dots++;
          break;
        case kGhostLook:
          level_.ghosts.push_back(Ghost(i, j));
          break;
        case '>':
          level_.pacman.push_back(Pacman(i, j));
          break;
      }
    }
  }

  if (level_.pacman.size() > 1 || level_.pacman.size() == 0) {
    throw out_of_range("Incorrect numbers of Pacman on the map!");
  }
}

void GameSys::StartOverLevel(vector<wstring>& map) {
  decrement_pacman_lives();
  level_.pacman[0].Ressurection(map);
  for (Ghost& g : level_.ghosts) {
    g.Resurrection(map);
  }
}

void GameSys::ProcessingLevel(vector<wstring>& map) {
  if (!level_.timer_ghost_slow_down.Check(350ms)) {
    for (auto& ghost : level_.ghosts) {
      ghost.Action(map).Processing(this, map, level_.ghosts);
    }
    level_.timer_ghost_slow_down.Start();
  }

  level_.pacman[0].Action(map).Processing(this, map, level_.ghosts);

  if (!level_.timer_to_scare_ghosts.Check(10000ms)) {
    EncourageGhosts();
  }
}

void GameSys::decrement_pacman_lives() { level_.pacman_lives--; };

void GameSys::decrement_num_dots() { --level_.num_dots; }

void GameSys::update_score(int points) { level_.score += points; }

void GameSys::ScareGhosts() {
  for (Ghost& g : level_.ghosts) {
    g.set_to_scared();
  }
  level_.timer_to_scare_ghosts.Start();
}

void GameSys::EncourageGhosts() {
  for (Ghost& g : level_.ghosts) {
   g.reset_scared();
  }
}
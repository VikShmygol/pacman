#pragma once
#include <string>
#include <vector>
#include "level_class.h"


using namespace std;

//class Level;

struct GameData {
  Level level;
  unsigned int current_level = 0;
  vector<wstring> map;
  vector<wstring> previous_map;
};


class GameSys {
 public:
// GameSys();
  void GameProcessing(const vector<string>& level_filename_vector,
                      vector<wstring>& map);

 private:
  GameData game_;
  void ScreenUpdate(vector<wstring>& map, size_t map_height, size_t map_width);
  void SetCursorPosition(int row, int col);
  void ShowConsoleCursor(bool show_flag);
};

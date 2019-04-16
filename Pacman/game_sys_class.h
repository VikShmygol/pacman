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
};


class GameSys {
 public:
// GameSys();
  void GameProcessing(const vector<string>& level_filename_vector,
                      vector<wstring>& map);

 private:
  GameData game_;

};

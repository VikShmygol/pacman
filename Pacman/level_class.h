#pragma once
#include <string>
#include <vector>
#include "ghost_class.h"

using namespace std;

//class Ghost;

struct LevelData {
  int pacman_lives = 3;
  int score = 0;
  int num_dots = 0;
  vector<Ghost> ghosts;
};

class Level {
 public:

  void LoadLevel(const string& level_filename, vector<wstring>& level_map);
  void ProcessingLevel(vector<wstring>& level_map);
  int get_pacman_lives() const;
  void decrement_pacman_lives();
  int get_num_dots() const;
  void decrement_num_dots();

 private:
  LevelData level_;
};

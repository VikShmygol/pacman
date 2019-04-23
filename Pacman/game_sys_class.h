#pragma once
#include <string>
#include <vector>
#include "delay_off_timer_class.h"
#include "ghost_class.h"
#include "pacman_class.h"

using namespace std;

struct GameData {
  unsigned int current_level = 0;
  vector<wstring> map;
};

struct LevelData {
  bool scaring_mode =
      false;  // if scaring mode is active, ghosts are vulnerable to Pacman
  size_t map_height;
  size_t map_width;
  int pacman_lives = 3;
  int score = 0;
  int num_dots = 0;
  vector<Ghost> ghosts;
  vector<Pacman> pacman;
  DelayOffTimer timer_to_scare_ghosts;
  DelayOffTimer timer_ghost_slow_down;
};

class GameSys {
 public:
  void GameProcessing(const vector<string>& level_filename_vector,
                      vector<wstring>& map);

  void decrement_pacman_lives();

  void decrement_num_dots();

  void update_score(int points);

 // Starting level over after each Pacman's death
  void StartOverLevel(vector<wstring>& map);

// Set ghosts to be vulnerable to Pacman
  void ScareGhosts();

 private:
  GameData game_;
  LevelData level_;

  void ScreenUpdate(vector<wstring>& map, size_t map_height, size_t map_width);

  void SetCursorPosition(int row, int col);

  void ShowConsoleCursor(bool show_flag);

  void LoadLevel(const string& level_filename, vector<wstring>& level_map);

  void ProcessingLevel(vector<wstring>& level_map);

  void EncourageGhosts();
};

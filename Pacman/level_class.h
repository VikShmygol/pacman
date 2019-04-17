#pragma once
#include <string>
#include <vector>
#include "ghost_class.h"
#include "pacman_class.h"
#include "delay_off_timer_class.h"

using namespace std;

// class Ghost;

struct LevelData {
  bool scaring_mode = false;  // if scaring mode is active, ghosts are vulnerable to Pacman
  int pacman_lives;
  int score = 0;
  int num_dots = 0;
  vector<Ghost> ghosts;
  vector<Pacman> pacman;
  DelayOffTimer timer_to_scare_ghosts;
};

class Level {
 public:
  void LoadLevel(const string& level_filename, vector<wstring>& level_map);
  void ProcessingLevel(vector<wstring>& level_map);
  int get_pacman_lives() const;
  void decrement_pacman_lives();
  int get_num_dots() const;
  void update_score(int points);
  int get_score() const;
  void ScareGhosts();
  void EncourageGhosts();

 private:
  LevelData level_;
};

#include "pch.h"
#include "level_class.h"
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include "common_functions.h"
#include "ghost_class.h"
#include <codecvt>
#include <fstream>

void Level::LoadLevel(const string& level_filename,
                      vector<wstring>& level_map) {

// Extracting the map data from Unicode file 
// into the vector of <wstring>
  wstring line;
  unsigned int size_rows = 0, size_cols = 0;
  locale::global(std::locale("fr_FR.UTF-8"));
  const locale empty_locale = std::locale::empty();
  typedef codecvt_utf8_utf16<wchar_t> converter_type;
  const converter_type* converter = new converter_type;
  const locale utf8_locale = std::locale(empty_locale, converter);
  wifstream stream(level_filename);
  stream.imbue(utf8_locale);

  stream >> size_rows >> size_cols;
  getline(stream, line);
  while (getline(stream, line)) {
    level_map.push_back(line);
  }

// Counting ghosts and dots
  for (int i = 0; i < size_rows; ++i) {
    for (int j = 0; j < size_cols; ++j) {
      switch (level_map[i][j]) {
        case '0':
        case '∙':
          level_.num_dots++;
          break;
        case 'M':
          level_.ghosts.push_back(Ghost(i, j));
          break;
      }
    }
  }
}

void Level::ProcessingLevel(vector<wstring>& map) {
   for (auto& ghost : level_.ghosts) {
    ghost.GhostAction(map);
  }
}
int Level::get_pacman_lives() const { return level_.pacman_lives; }
void Level::decrement_pacman_lives() { level_.pacman_lives--; };
int Level::get_num_dots() const { return level_.num_dots; }
void Level::decrement_num_dots() { level_.num_dots--; }

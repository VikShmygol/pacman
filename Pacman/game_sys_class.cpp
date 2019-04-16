#include "pch.h"
#include "game_sys_class.h"
#include <codecvt>
#include <iostream>
#include <locale>
#include "level_class.h"
#include <thread>
#include <chrono>

//GameSys::GameSys(){};

void GameSys::GameProcessing(const vector<string>& level_filename_vector,
                             vector<wstring>& map) {
 
  while (true) {
    system("cls");
    if (!game_.level.get_num_dots() && game_.level.get_pacman_lives() &&
        game_.current_level < level_filename_vector.size()) {
      game_.level.LoadLevel(level_filename_vector[game_.current_level], map);
      game_.current_level++;
    } else if (!game_.level.get_num_dots()) {
      cout << "You won, congratulations!" << endl;
      system("PAUSE");
      break;
    } 
    else if (!game_.level.get_pacman_lives()) {
      cout << "Try again!" << endl;
      system("PAUSE");
      game_.level.LoadLevel(level_filename_vector[game_.current_level], map);
    } else {
      game_.level.ProcessingLevel(map);
    }

//   locale::global(std::locale("fr_FR.UTF-8"));// encoding settings for proper
//    wcout.imbue(std::locale("zh_CN.utf8"));// wstring output

    for (wstring& s : map) {
      wcout << s << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(100));
  }
}

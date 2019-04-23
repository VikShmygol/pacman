#include "pch.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "game_sys_class.h"


//#define NOMINMAX
//#define WIN32_LEAN_AND_MEAN


int main(void) {
  vector<string> vector_filename{"Level_1.txt"};
  vector<wstring> map;
  GameSys game;
  try {
    game.GameProcessing(vector_filename, map);
  } catch (exception& ex) {
    cerr << ex.what() << endl;
    system("PAUSE");
  }



  return 0;
}




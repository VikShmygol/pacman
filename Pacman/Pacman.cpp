#include "pch.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "game_sys_class.h"

int main(void) {
  vector<string> vector_filename{"Level_1.txt"};
  vector<wstring> map;
  GameSys game;
  game.GameProcessing(vector_filename, map);

  



  return 0;
}




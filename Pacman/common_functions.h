#pragma once
#include <string>
//#include <locale>
//#include <codecvt>
using namespace std;

/* Simple function to check if a given character
   belongs to a given string */
inline bool FindCharacter(const wstring& str, const wchar_t& character) {
  return str.find_first_of(character) != wstring::npos;
}

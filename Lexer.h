//
// Created by shlomo on 12/12/2019.
//
#ifndef EX3_LEXER_H
#define EX3_LEXER_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Lexer {
  string file_name;
  static bool isApos(char);
  static bool isSpace(char);
  int separationLoc(string &);
 public:
  Lexer(string);
  bool lexer(vector<string> *);

};

#endif //EX3_LEXER_H
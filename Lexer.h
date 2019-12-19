//
// Created by shlomo on 12/12/2019.
//
#ifndef EX3__LEXER_H_
#define EX3__LEXER_H_

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Lexer {
  string file_name;
  static bool isParenthesesOrBlank(char c);
 public:
  Lexer(string);
  bool lexer(vector<string>*);

};

#endif //EX3__LEXER_H_

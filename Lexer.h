//
// Created by shlomo on 12/12/2019.
//
//daniel
#ifndef EX3__LEXER_H_
#define EX3__LEXER_H_

#include <iostream>
#include <vector>
using namespace std;

class Lexer {
  string file_name;
 public:
  Lexer(string);
  bool lexer(vector<string>*);
};

#endif //EX3__LEXER_H_

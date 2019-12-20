//
// Created by shlomo on 13/12/2019.
//

#ifndef EX3__COMMAND_H_
#define EX3__COMMAND_H_
#include "iostream"
#include "vector"
using namespace std;
class Command {
 public:
  Command() {};
  virtual int execute(vector<string>*,int) = 0;
  virtual ~Command() {};
};

#endif //EX3__COMMAND_H_


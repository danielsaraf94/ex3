//
// Created by daniels on 21/12/2019.


#ifndef EX3_3__COMMAND_H_
#define EX3_3__COMMAND_H_
#include "iostream"
#include "vector"
using namespace std;
class Command {
 public:
  Command() {};
  virtual int execute(vector<string> *, int) = 0;
  virtual ~Command() {};
};

#endif //EX3_3__COMMAND_H_

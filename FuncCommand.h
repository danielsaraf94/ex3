//
// Created by shlomo on 21/12/2019.

#ifndef EX3_1__FUNCCOMMAND_H_
#define EX3_1__FUNCCOMMAND_H_
#include "vector"
#include "iostream"
#include "queue"
#include "Command.h"
#include "CommandManager.h"

using namespace std;

class FuncCommand : public Command {
  int index;
  bool args;
  vector<string> *string_vec;
  int return_index;
  CommandManager *manager;
  Globals* globals;
 public:
  FuncCommand(vector<string> *, int, CommandManager *, Globals *);
  void setIndex(int);
  int execute(vector<string> *, int);
  int returnIndex();
  void setArgs();
};

#endif //EX3_1__FUNCCOMMAND_H_

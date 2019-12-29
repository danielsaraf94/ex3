//
// Created by shlomo on 13/12/2019.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H

#include "Command.h"
#include "iostream"
#include "unordered_map"
#include "queue"
#include "Data.h"
#include "Globals.h"

using namespace std;

class Var : public Command {
  unordered_map<string, Command *> *str_command_map;
  unordered_map<string, Data *> *varName_data_map;
  unordered_map<string, Data *> *sim_num_map;
  queue<string> *update_simulator_q;
  Globals *globals;
  int getSign(string *, int *);
 public:
  Var(unordered_map<string, Command *> *,
      unordered_map<string, Data *> *,
      unordered_map<string, Data *> *,
      queue<string> *,
      Globals *);
  int execute(vector<string> *, int);
  static bool isParentheses(char);
};

#endif //EX3_VAR_H
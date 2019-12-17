//
// Created by shlomo on 13/12/2019.
//

#ifndef EX3__VAR_H_
#define EX3__VAR_H_

#include "Command.h"
#include "iostream"
#include "map"
#include "Data.h"

using namespace std;

class Var : public Command {
  map<string, Command *> *str_command_map;
  map<string, Data *> *varName_data_map;
  map<string, Data*> *sim_num_map;
  int getSign(string *, int *);
 public:
  Var(map<string, Command *> *, map<string, Data *> *, map<string,Data*> *);
  void execute(string *);
  ~Var() {};
};

#endif //EX3__VAR_H_


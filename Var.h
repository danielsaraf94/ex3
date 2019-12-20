//
// Created by shlomo on 13/12/2019.


#ifndef EX3_VAR_H
#define EX3_VAR_H

#include "Command.h"
#include "iostream"
#include "unordered_map"
#include "queue"
#include "Data.h"

using namespace std;

class Var : public Command {
  unordered_map<string, Data *> *varName_data_map;
  unordered_map<string, Data *> *sim_num_map;
  int getSign(string *, int *);
 public:
  Var(unordered_map<string, Data *> *, unordered_map<string, Data *> *);
  int execute(vector<string> *, int);
  ~Var() {};
};

#endif //EX3_VAR_H
//
// Created by daniels on 20/12/2019.
//

#include "WhileCommand.h"
WhileCommand::WhileCommand(unordered_map<string, Command *> *c_m, unordered_map<string, Data *> *s_t)
    : c_m(c_m), s_t(s_t) {
}
int WhileCommand::execute(vector<string> *string_vec, int i) {
  string* condition = string_vec[i+1];
  while (checkcCondition(condition){

  }
  return 0;
}

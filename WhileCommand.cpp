//
// Created by daniels on 20/12/2019.
//

#include <regex>
#include "WhileCommand.h"
WhileCommand::WhileCommand(unordered_map<string, Command *> *cm, vector<string> *sv)
    : c_m(cm), s_v(sv) {
}
int WhileCommand::execute(vector<string> *string_vec, int i) {
  string condition = (*string_vec)[i];
  //make if condition
  ConditionParser *c = (ConditionParser *) (*c_m)["if"];
  while (c->isTrue(condition)) {
    c->execute(s_v, i);
  }
  return c->returnIndex(s_v, i) - i + 1;
}
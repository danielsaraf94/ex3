//
// Created by daniels on 20/12/2019.
//

#include <regex>
#include "WhileCommand.h"
WhileCommand::WhileCommand(unordered_map<string, Command *> *c_m,
                           unordered_map<string, Data *> *s_t,
                           vector<string> *s_v)
    : c_m(c_m), s_t(s_t), s_v(s_v) {
}
int WhileCommand::execute(vector<string> *string_vec, int i) {
  string condition = (*string_vec)[i];
  ConditionParser *c = (ConditionParser *) (*c_m)["if"];
  while (c->isTrue(condition)) {
    c->execute(s_v,i);
  }
  return c->returnIndex(s_v,i)-i+1;
}
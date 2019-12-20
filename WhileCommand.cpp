//
// Created by daniels on 20/12/2019.
//

#include "WhileCommand.h"
WhileCommand::WhileCommand(unordered_map<string, Command *> *c_m, unordered_map<string, Data *> *s_t)
    : c_m(c_m), s_t(s_t) {
}
int WhileCommand::execute(vector<string> *string_vec, int i) {
  string condition = (*string_vec)[i + 1];
  while (checkCondition(condition)) {

    for (int i = 0; i < string_vec.size();) {
      Command *c = command_map[string_vec[i]];
      if (c) {
        i += c->execute(&string_vec, i + 1);
      } else {
        if (symbol_table[string_vec[i]]) {
          varAssign(string_vec[i], string_vec[i + 1], symbol_table, update_simulator_q);
          i += 2;
        }
      }
      return 0;
    }
  }
}
bool WhileCommand::checkCondition(string) {
  return false;
}

//
// Created by shlomo on 20/12/2019.


#include <regex>
#include "ConditionParser.h"
ConditionParser::ConditionParser(unordered_map<string, Command *> *map1,
                                 unordered_map<string, Data *> *map2,
                                 Globals *g) {
  this->command_map = map1;
  this->symbol_table = map2;
  this->globals = g;
}

int ConditionParser::execute(vector<string> *string_vec, int i) {
  //calculate how much indexes to move forward when return from execute
  int return_index = returnIndex(string_vec, i) - i;
  int first_index = i - 1;
  Data d(globals, symbol_table);
  if (d.fromStringToValue((*string_vec)[i])) {
    i++;
    // if the condoion is true - execute all the commands in the if scope
    while (i < first_index + return_index - 1) {
      Command *c = (*command_map)[(*string_vec)[i]];
      i += c->execute(string_vec, i + 1);
    }
  }
  return return_index + 1;
}

int ConditionParser::returnIndex(vector<string> *string_vec, int i) {
  //calculate how much indexes to move forward when return from execute
  while ((int) (*string_vec)[i].find("{") == -1) {
    i++;
  }
  this->q.push("{");
  i++;
  while (!this->q.empty()) {
    if ((int) (*string_vec)[i].find("{") != -1) {
      this->q.push("{");
    }
    if ((int) (*string_vec)[i].find("}") != -1) {
      this->q.pop();
    }
    i++;
  }
  return i;
}
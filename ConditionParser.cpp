//
// Created by shlomo on 20/12/2019.
//

#include "ConditionParser.h"
ConditionParser::ConditionParser(unordered_map<string, Command *> *map1, unordered_map<string, Data *>* map2) {
  this->command_map = map1;
  this->symbol_table=map2;
}

int ConditionParser::exectue(vector<string> *string_vec, int i) {
  int return_index = returnIndex(string_vec, i);
  if (isTrue((*string_vec)[i])) {
    while (i != return_index - 1) {
      Command* c = (*command_map)[(*string_vec)[i]];
      i+=c->execute(string_vec,i+1);
    }
  }
  return return_index;
}

int ConditionParser::returnIndex(vector<string> *string_vec, int i) {
  while ((*string_vec)[i].find("{") == -1) {
    i++;
  }
  this->queue.push("{");
  while (this->queue.empty() == false) {
    if ((*string_vec)[i].find("{") != -1) {
      this->queue.push("{");
    }
    if ((*string_vec)[i].find("}") != -1) {
      this->queue.pop();
    }
    i++;
  }
  return i;
}
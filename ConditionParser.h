//
// Created by shlomo on 20/12/2019.

#ifndef EX3_1_CMAKE_BUILD_DEBUG_CONDITIONPARSER_H_
#define EX3_1_CMAKE_BUILD_DEBUG_CONDITIONPARSER_H_

#include "Command.h"
#include <unordered_map>
#include "list"
#include <queue>
#include "Data.h"
class ConditionParser : public Command {
  unordered_map<string, Data *> *symbol_table;
  unordered_map<string, Command *> *command_map;
  queue<string> q;
  Globals *globals;
 public:
  ConditionParser(unordered_map<string, Command *> *, unordered_map<string, Data *> *, Globals *);
  int execute(vector<string> *, int i);
  int returnIndex(vector<string> *, int);
};

#endif //EX3_1_CMAKE_BUILD_DEBUG_CONDITIONPARSER_H_

//
// Created by shlomo on 21/12/2019.


#ifndef EX3_1__COMMANDMANAGER_H_
#define EX3_1__COMMANDMANAGER_H_
#include "unordered_map"
#include "Command.h"
#include "Data.h"
#include <vector>
#include <unordered_map>
#include "OpenServerCommand.h"
#include <queue>
#include "ClientConnectCommand.h"
#include "Globals.h"
#include "PrintCommand.h"
#include "Var.h"
#include "SleepCommand.h"
#include "ConditionParser.h"
#include "WhileCommand.h"

class CommandManager {
  vector<string>* string_vec;
  Globals *globals;
  queue<string> update_simulator_q;
  unordered_map<string,Command*> command_map;
  unordered_map<string,Data*> symbol_table;
  unordered_map<string,Data*> sim_table;
  void initializeCommandMap();
 public:
  CommandManager(vector<string>*,Globals*);
  unordered_map<string,Command*>* getCommnadMap();
  unordered_map<string,Data*>* getSymbolMap();
  unordered_map<string,Data*>* getSimMap();
  int addFuncCommand(int);
  ~CommandManager();

};

#endif //EX3_1__COMMANDMANAGER_H_

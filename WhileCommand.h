//
// Created by daniels on 20/12/2019.
//

#ifndef EX3_3__WHILECOMMAND_H_
#define EX3_3__WHILECOMMAND_H_
#include <vector>
#include <unordered_map>
#include "Command.h"
#include "Lexer.h"
#include "Data.h"
#include "OpenServerCommand.h"
#include <queue>
#include "ClientConnectCommand.h"
#include "Globals.h"
#include "PrintCommand.h"
#include "Var.h"
#include "SleepCommand.h"


class WhileCommand : public Command {
  unordered_map<string, Command *> * c_m;
  unordered_map<string, Data *> * s_t;
  int execute(vector<string> *,int);
 public:
  WhileCommand(unordered_map<string, Command *> *, unordered_map<string, Data *> *);
};

#endif //EX3_3__WHILECOMMAND_H_
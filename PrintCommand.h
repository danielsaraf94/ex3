//
// Created by daniels on 19/12/2019.

#ifndef EX3_3_PRINTCOMMAND_H
#define EX3_3_PRINTCOMMAND_H

#include "Command.h"
#include "iostream"
#include <unistd.h>
#include "unordered_map"
#include "Data.h"
using namespace std;

class PrintCommand : public Command {
  unordered_map<string, Data *> *symbol_table;
 public:
  int execute(vector<string>*,int);
  PrintCommand(unordered_map<string, Data *> *s);
};
#endif //EX3_3_PRINTCOMMAND_H
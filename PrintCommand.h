//
// Created by daniels on 19/12/2019.

#ifndef EX3_3__PRINTCOMMAND_H_
#define EX3_3__PRINTCOMMAND_H_

#include "Command.h"
#include "iostream"
#include <unistd.h>"
#include "unordered_map"
#include "Data.h"
using namespace std;

class PrintCommand : public Command {
  unordered_map<string, Data *> *symbol_table;
  void execute(string *s);
 public:
  PrintCommand(unordered_map<string, Data *> *s) : symbol_table(s) {}

};
#endif //EX3_3__PRINTCOMMAND_H_

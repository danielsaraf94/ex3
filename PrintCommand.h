//
// Created by daniels on 19/12/2019.

#ifndef EX3_3__PRINTCOMMAND_H_
#define EX3_3__PRINTCOMMAND_H_

#include "Command.h"
#include "iostream"
#include <unistd.h>"
using namespace std;

class PrintCommand : public Command {
  void execute(string *s) { cout << *s << endl; }
};
#endif //EX3_3__PRINTCOMMAND_H_

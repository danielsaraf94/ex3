
// Created by daniels on 19/12/2019.

#ifndef EX3_3__SLEEPCOMMAND_H_
#define EX3_3__SLEEPCOMMAND_H_
#include <thread>
#include "Command.h"
#include "iostream"
#include <unistd.h>
#include <iostream>
#include <chrono>

using namespace std;

class SleepCommand : public Command {
  unordered_map<string, Data *> *symbol_table;
  Globals *globals;
 public:
  SleepCommand(unordered_map<string, Data *> *st, Globals *g) : symbol_table(st), globals(g) {}
  int execute(vector<string> *string_vec, int i) {
    Data d(globals, symbol_table);
    std::this_thread::sleep_for(std::chrono::milliseconds((int) d.fromStringToValue((*string_vec)[i])));
    return 2;
  }
};
#endif //EX3_3__SLEEPCOMMAND_H_

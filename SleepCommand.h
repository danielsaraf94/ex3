//
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
 public:
  int execute(vector<string>* string_vec,int i){
    Interpreter interpreter;
    auto *exp = interpreter.interpret((*string_vec)[i]);
    std::this_thread::sleep_for (std::chrono::milliseconds((int)exp->calculate()));
    delete(exp);
    return 2;
  }
};
#endif //EX3_3__SLEEPCOMMAND_H_

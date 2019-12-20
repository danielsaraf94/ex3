//
// Created by daniels on 19/12/2019.

#ifndef EX3_3__SLEEPCOMMAND_H_
#define EX3_3__SLEEPCOMMAND_H_

#include "Command.h"
#include "iostream"
#include <unistd.h>
using namespace std;

class SleepCommand : public Command {
 public:
  int execute(vector<string>* string_vec,int i){
    sleep(stoi((*string_vec)[i])/1000);
    return 2;
  }
};
#endif //EX3_3__SLEEPCOMMAND_H_

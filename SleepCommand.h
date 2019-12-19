//
// Created by daniels on 19/12/2019.
//

#ifndef EX3_3__SLEEPCOMMAND_H_
#define EX3_3__SLEEPCOMMAND_H_

#include "Command.h"
#include "iostream"
#include <unistd.h>
using namespace std;

class SleepCommand : public Command {
  void execute(string *s){
    sleep(stoi(*s)/1000);
  }
};
#endif //EX3_3__SLEEPCOMMAND_H_

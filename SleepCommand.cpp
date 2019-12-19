//
// Created by daniels on 19/12/2019.
//
#include "SleepCommand.h"
using namespace std;
#include <unistd.h>
void SleepCommand::execute(string * s) {
  sleep(stoi(*s)/1000);
}

//
// Created by shlomo on 13/12/2019.
//

#ifndef EX3_CMAKE_BUILD_DEBUG_DATA_H_
#define EX3_CMAKE_BUILD_DEBUG_DATA_H_
#include "Command.h"
#include "iostream"
using namespace std;

class Data : public Command {
  double value;
  string sim;
  //represents the direction of the biding
  int sign;
 public:
  Data(){};
  Data(string, int);
  virtual void execute(string*);
  void setValue(double);
  double getValue();

};

#endif //EX3_CMAKE_BUILD_DEBUG_DATA_H_


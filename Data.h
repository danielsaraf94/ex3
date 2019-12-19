//
// Created by shlomo on 13/12/2019.
//

#ifndef EX3_CMAKE_BUILD_DEBUG_DATA_H_
#define EX3_CMAKE_BUILD_DEBUG_DATA_H_
#include "Command.h"
#include "iostream"
#include "queue"
using namespace std;

class Data {
  double value;
  string sim;
  //represents the direction of the biding, 1 : ->, 2: <- , 3: =
  int sign;
 public:
  Data(){};
  Data(string, int);
  void setValue(double);
  double getValue();
  string getSim();
  int getSign() const;

};

#endif //EX3_CMAKE_BUILD_DEBUG_DATA_H_


//
// Created by shlomo on 13/12/2019.
//

#ifndef EX3_CMAKE_BUILD_DEBUG_DATA_H_
#define EX3_CMAKE_BUILD_DEBUG_DATA_H_
#include "Command.h"
#include "iostream"
#include "queue"
#include "unordered_map"
using namespace std;

class Data : public Command {
  double value;
  string varName;
  string sim;
  unordered_map<string, Data *> *symbol_table;
  queue<string> *update_simulator_q;
  //represents the direction of the biding, 1 : ->, 2: <- , 3: =
  int sign;
 public:
  Data() {};
  Data(string, string, int, queue<string> *, unordered_map<string, Data *> *);
  virtual int execute(vector<string> *, int);
  void setValue(double);
  double getValue();
  string getSim();
  int getSign();
  int getIndexBeforeOp(string, int);
  int getIndexAfterOp(string, int);
  string getVarName();

};

#endif //EX3_CMAKE_BUILD_DEBUG_DATA_H_


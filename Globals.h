//
// Created by daniels on 19/12/2019.
//

#ifndef EX3_3__GLOBALS_H_
#define EX3_3__GLOBALS_H_
#include <mutex>
using namespace std;
class Globals {
 public:
  mutex locker;
  bool to_close;
  int sizeOfvalue;
  char value[1024];
  Globals() { this->to_close = false; }
};
#endif //EX3_3__GLOBALS_H_

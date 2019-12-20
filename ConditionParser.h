//
// Created by shlomo on 20/12/2019.
//

#ifndef EX3_1_CMAKE_BUILD_DEBUG_CONDITIONPARSER_H_
#define EX3_1_CMAKE_BUILD_DEBUG_CONDITIONPARSER_H_

#include <Command.h>
class ConditionParser: public Command {
 public:
  bool isTrue();
  int exectue(vector<string>*,int i);
};

#endif //EX3_1_CMAKE_BUILD_DEBUG_CONDITIONPARSER_H_

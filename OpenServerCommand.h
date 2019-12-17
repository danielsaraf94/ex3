//
// Created by shlomo on 16/12/2019.
//

#ifndef EX3__OPENSERVERCOMMAND_H_
#define EX3__OPENSERVERCOMMAND_H_
#include "Command.h"
#include "map"
#include "Data.h"

class OpenServerCommand : public Command {
  int socketfd;
  double array[1024];
  map<int, string> numTosim;
  map<string, Data *> *sim_table;
 public:
  OpenServerCommand(map<string, Data *> *map);
  void initialSimToNumMap();
  void readData(char *buffer);
  void execute(string *);

};

#endif //EX3__OPENSERVERCOMMAND_H_

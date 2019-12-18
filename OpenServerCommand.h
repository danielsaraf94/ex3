//
// Created by shlomo on 16/12/2019.
//

#ifndef EX3__OPENSERVERCOMMAND_H_
#define EX3__OPENSERVERCOMMAND_H_
#include "Command.h"
#include "unordered_map"
#include "Data.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <chrono>
#include <thread>

class OpenServerCommand : public Command {
  int socketfd;
  double array[1024];
 unordered_map<int, string> numTosim;
 unordered_map<string, Data *> *sim_table;
 public:
  OpenServerCommand(unordered_map<string, Data *> *map);
  void initialSimToNumMap();
  void readData(char *buffer);
  void execute(string *);

};

#endif //EX3__OPENSERVERCOMMAND_H_

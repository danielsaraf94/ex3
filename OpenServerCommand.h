//
// Created by shlomo on 16/12/2019.

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
#include "Globals.h"
//

class OpenServerCommand : public Command {
  int socketfd;
  double array[1024];
 unordered_map<int, string> numTosim;
 unordered_map<string, Data *> *sim_table;
 Globals* glob;
 public:
  thread t;
  OpenServerCommand(unordered_map<string, Data *> *map,Globals*);
  void initialSimToNumMap();
  int execute(vector<string> *,int);
  static void readFromClient(int,int,Globals*, unordered_map<string, Data *> *, unordered_map<int, string> *);
};

#endif //EX3__OPENSERVERCOMMAND_H_

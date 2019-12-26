//
// Created by daniels on 16/12/2019.
//

#ifndef EX3_3__CLIENTCONNECTCOMMAND_H_
#define EX3_3__CLIENTCONNECTCOMMAND_H_

#include <cstring>
#include <queue>
#include "Command.h"
#include "Data.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include "Globals.h"

using namespace std;
//
class ClientConnectCommand : public Command {
  string ip;
  string port;
  unordered_map<string, Data *> *symbol_table;
  queue<string> *update_simulator_q;
  sockaddr_in address;
  int client_socket;
  Globals *glob;
 public:
  ClientConnectCommand(unordered_map<string, Data *> *, queue<string> *, Globals *);
  int execute(vector<string>*,int);
  void extractAddressFromString(string *);
  static void updateServer(unordered_map<string, Data *> *, queue<string> *, int *,Globals*);
};

#endif //EX3_3__CLIENTCONNECTCOMMAND_H_

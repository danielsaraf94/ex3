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

using namespace std;
//
class ClientConnectCommand : public Command {
  string ip;
  string port;
  unordered_map<string, Data *>* symbol_table;
  queue<string>* update_simulator_q;
  sockaddr_in address;
  int client_socket;
  bool to_close = false;
 public:
  thread t;
  ClientConnectCommand(unordered_map<string, Data *> *, queue<string> *);
  void execute(string *);
  void extractAddressFromString(string *);
  static void updateServer(bool*, unordered_map<string, Data *> *, queue<string> *, int *);
  void closeClient();
};

#endif //EX3_3__CLIENTCONNECTCOMMAND_H_

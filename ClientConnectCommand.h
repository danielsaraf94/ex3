//
// Created by daniels on 16/12/2019.
//

#ifndef EX3_3__CLIENTCONNECTCOMMAND_H_
#define EX3_3__CLIENTCONNECTCOMMAND_H_

#include "Command.h"
#include "Data.h"
#include <string>
#include <iostream>
#include <map>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class ClientConnectCommand : public Command {
  string ip;
  string port;
  map <string, Data *> symbol_table;
  sockaddr_in address;
  int client_socket;
 public:
  ClientConnectCommand(map<string, Data *> &);
  void execute(string *);
  void extractAddressFromString(string *);
  void updateServer(char []);
  void closeClient();
};

#endif //EX3_3__CLIENTCONNECTCOMMAND_H_

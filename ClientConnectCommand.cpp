//
// Created by daniels on 16/12/2019.
//
#include "ClientConnectCommand.h"

ClientConnectCommand::ClientConnectCommand(unordered_map<string, Data *> *s_t, queue<string> *u_s_q)
    : symbol_table(s_t), update_simulator_q(u_s_q) {
}
void ClientConnectCommand::execute(string *s) {
  extractAddressFromString(s);

  //create socket
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    //error
    std::cerr << "Could not create a socket" << std::endl;
    exit(1);
  }

  //We need to create a sockaddr obj to hold address of server

  address.sin_family = AF_INET;//IP4
  address.sin_addr.s_addr = inet_addr(ip.c_str());  //the localhost address
  address.sin_port = htons(stoi(port));
  //we need to convert our number (both port & localhost)
  // to a number that the network understands

  // Requesting a connection with the server on local host with port
  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    std::cerr << "Could not connect to host server" << std::endl;
    exit(2);
  } else {
    std::cout << "Client is now connected to server" << std::endl;
  }
  t = thread(updateServer, &to_close, symbol_table, update_simulator_q, &client_socket);

}
void ClientConnectCommand::extractAddressFromString(string *str) {
  string s = *str;
  int ipStart = 0, ipLen = 0, portStart = 0, portEnd = 0;
  int i;
  for (i = 0; i < s.length(); i++) {
    if ((s[i] < '0' || s[i] > '9') && s[i] != '.')
      continue;
    ipStart = i;
    break;
  }
  for (; i < s.length(); i++) {
    if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
      ipLen++;
      continue;
    }
    break;
  }
  for (; i < s.length(); i++) {
    if ((s[i] < '0' || s[i] > '9') && s[i] != '.')
      continue;
    portStart = i;
    break;
  }

  port = s.substr(portStart, 4);
  ip = s.substr(ipStart, ipLen);
}
void ClientConnectCommand::updateServer(bool *to_close,
                                        unordered_map<string, Data *> *symbol_table,
                                        queue<string> *update_simulator_q,
                                        int *client_socket) {
  string var_name;
  Data *var;
  bool is_q_empty = true;
  while (!(*to_close)) {
    while (is_q_empty) {
      Globals::locker.lock();
      if (!update_simulator_q->empty()) is_q_empty = false;
      Globals::locker.unlock();
    }
    Globals::locker.lock();
    var_name = update_simulator_q->front();
    update_simulator_q->pop();
    var = symbol_table->find(var_name)->second;
    Globals::locker.unlock();
    string s = "set " + var->getSim() + " " + to_string(var->getValue()) + "\r\n";
    char c[s.length() + 1];
    strcpy(c, s.c_str());
    int is_sent = send(*client_socket, c, strlen(c), 0);
    if (is_sent == -1) {
      std::cout << "Error sending message" << std::endl;
    } else {
      std::cout << "message sent to server" << std::endl;
    }
    is_q_empty = true;
  }
  close(*client_socket);
}

void ClientConnectCommand::closeClient() {
  to_close = true;
}


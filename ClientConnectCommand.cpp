//
// Created by daniels on 16/12/2019.
//
#include "ClientConnectCommand.h"

ClientConnectCommand::ClientConnectCommand(unordered_map<string, Data *> *s_t, queue<string> *u_s_q, Globals *g)
    : symbol_table(s_t), update_simulator_q(u_s_q), glob(g) {
}
int ClientConnectCommand::execute(vector<string>* string_vec,int i) {
  extractAddressFromString(&(*string_vec)[i]);

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
  Interpreter inter;
  address.sin_port = htons((int)(inter.interpret(port)->calculate()));
  //we need to convert our number (both port & localhost)
  // to a number that the network understands


  // Requesting a connection with the server on local host with port
  std::cout << "try to connect to simulator" << std::endl;
  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    std::cerr << "connected failed" << std::endl;
    exit(2);
  } else {
    std::cout << "connected succeeded" << std::endl;
  }
  t = thread(updateServer, symbol_table, update_simulator_q, &client_socket, glob);
  return 2;
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
    if ((s[i] < '0' || s[i] > '9') && s[i] != '.' && s[i] != '(')
      continue;
    portStart = i;
    break;
  }

  port = s.substr(portStart, s.length()-portStart-1);
  ip = s.substr(ipStart, ipLen);
}
void ClientConnectCommand::updateServer(unordered_map<string, Data *> *symbol_table,
                                        queue<string> *update_simulator_q,
                                        int *client_socket, Globals *g) {
  string var_name;
  Data *var;
  bool is_q_empty = true;
  while (!(g->to_close)) {
    while (is_q_empty) {
      g->locker.lock();
      if (!update_simulator_q->empty()) is_q_empty = false;
      g->locker.unlock();
    }
    g->locker.lock();
    var_name = update_simulator_q->front();
    update_simulator_q->pop();
    var = symbol_table->find(var_name)->second;
    string sim = var->getSim().substr(1, var->getSim().length());
    string s = "set " + var->getSim() + " " + to_string(var->getValue()) + "\r\n";
    g->locker.unlock();
    char c[s.length() + 1];
    strcpy(c, s.c_str());
    int is_sent = send(*client_socket, c, strlen(c), 0);
    if (is_sent == -1) {
      std::cout << "Error sending message" << std::endl;
    }
    is_q_empty = true;
  }
  close(*client_socket);
}


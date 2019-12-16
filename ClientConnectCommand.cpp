//
// Created by daniels on 16/12/2019.
//

#include <cstring>
#include "ClientConnectCommand.h"

ClientConnectCommand::ClientConnectCommand(map<string, Data *> &s_t) : symbol_table(s_t) {

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
void ClientConnectCommand::updateServer(char s[]) {
  int is_sent = send(client_socket, s, strlen(s), 0);
  if (is_sent == -1) {
    std::cout << "Error sending message" << std::endl;
  } else {
    std::cout << "Hello message sent to server" << std::endl;
  }
}

void ClientConnectCommand::closeClient() {
  close(client_socket);
}
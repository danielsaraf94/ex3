//
// Created by shlomo on 16/12/2019.
//

#include "OpenServerCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <chrono>
#include <thread>
OpenServerCommand::OpenServerCommand(map<string, Data *> *map) {
  this->sim_table = map;
  //create socket
  this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    //error
    std::cerr << "Could not create a socket" << std::endl;
    exit(1);
  }
}
void OpenServerCommand::execute(string *str) {
  const char *portName = str->substr(1, str->length() - 2).c_str();
  int port = atoi(portName);
  //bind socket to IP address
  // we first need to create the sockaddr obj.
  sockaddr_in address; //in means IP4
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
  address.sin_port = htons(port);
  //we need to convert our number
  // to a number that the network understands.

  //the actual bind command
  if (bind(this->socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    cerr << "Could not bind the socket to an IP" << endl;
    exit(1);
  }

  //making socket listen to the port
  if (listen(this->socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
    cerr << "Error during listening command" << endl;
    exit(1);
  } else {
    cout << "Server is now listening ..." << endl;
  }
  int client_socket = accept(this->socketfd, (struct sockaddr *) &address,
                             (socklen_t *) &address);
  if (client_socket == -1) {
    cerr << "Error accepting client" << endl;
    exit(1);
  }
  close(this->socketfd);
  //reading from client
  char buffer[1024] = {0};
//  while(true){
  //   std::this_thread::sleep_for(std::chrono::milliseconds(10));
  int valread = read(client_socket, buffer, 1024);
  cout<<buffer<<endl;

  // }
}
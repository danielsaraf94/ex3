//
// Created by shlomo on 16/12/2019.
//

#include "OpenServerCommand.h"
OpenServerCommand::OpenServerCommand(unordered_map<string, Data *> *map) {
  this->sim_table = map;
  //create socket
  this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    //error
    std::cerr << "Could not create a socket" << std::endl;
    exit(1);
  }
  initialSimToNumMap();
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
  char *p = buffer;
  while (true) {
    this_thread::sleep_for(std::chrono::milliseconds(10));
    int valread = read(client_socket, buffer, 1024);
    readData(p);
  }
}
void OpenServerCommand::readData(char *buffer) {
  char *end = buffer;
  for (int i = 0; i < 24; i++) {
    if((*this->sim_table).find(this->numTosim[i])==this->sim_table->end()){
      continue;
    }
    (*this->sim_table)[this->numTosim[i]]->setValue(strtod(end, &end));
    end++;
  }
}
void OpenServerCommand::initialSimToNumMap() {
  this->numTosim[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
  this->numTosim[1] = "//instrumentation/heading-indicator/offset-deg";
  this->numTosim[2] = "/instrumentation/altimeter/indicated-altitude-ft";
  this->numTosim[3] = "/instrumentation/altimeter/pressure-alt-ft";
  this->numTosim[4] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
  this->numTosim[5] = "/instrumentation/attitude-indicator/indicated-roll-deg";
  this->numTosim[6] = "/instrumentation/attitude-indicator/internal-pitch-deg";
  this->numTosim[7] = "/instrumentation/attitude-indicator/internal-roll-deg";
  this->numTosim[8] = "/instrumentation/encoder/indicated-altitude-ft";
  this->numTosim[9] = "/instrumentation/encoder/pressure-alt-ft";
  this->numTosim[10] = "/instrumentation/gps/indicated-altitude-ft";
  this->numTosim[11] = "/instrumentation/gps/indicated-ground-speed-kt";
  this->numTosim[12] = "/instrumentation/gps/indicated-vertical-speed";
  this->numTosim[13] = "/instrumentation/heading-indicator/indicated-heading-deg";
  this->numTosim[14] = "/instrumentation/magnetic-compass/indicated-heading-deg";
  this->numTosim[15] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
  this->numTosim[16] = "/instrumentation/turn-indicator/indicated-turn-rate";
  this->numTosim[17] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
  this->numTosim[18] = "/controls/flight/aileron";
  this->numTosim[19] = "/controls/flight/elevator";
  this->numTosim[20] = "/controls/flight/rudder";
  this->numTosim[21] = "/controls/flight/flaps";
  this->numTosim[22] = "/controls/engines/engine/throttle";
  this->numTosim[23] = "/engines/engine/rpm";
}

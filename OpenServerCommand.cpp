
// Created by shlomo on 16/12/2019.


#include "OpenServerCommand.h"
#include "ex1.h"
OpenServerCommand::OpenServerCommand(unordered_map<string, Data *> *map, Globals *g) {
  glob = g;
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
int OpenServerCommand::execute(vector<string> *string_vec, int i) {
  Interpreter interpreter;
  auto *exp = interpreter.interpret((*string_vec)[i]);
  double port = exp->calculate();
  delete(exp);
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
    cout << "waiting for simulator to connect" << endl;
  }
  int client_socket = accept(this->socketfd, (struct sockaddr *) &address,
                             (socklen_t *) &address);
  if (client_socket == -1) {
    cerr << "error accepting client" << endl;
    exit(1);
  }
  cout << "simulator connected" << endl;
  thread t(readFromClient, client_socket, this->socketfd, glob, sim_table, &numTosim);
  t.detach();
  return 2;
}

void OpenServerCommand::initialSimToNumMap() {
  this->numTosim[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
  this->numTosim[1] = "/sim/time/warp";
  this->numTosim[2] = "/controls/switches/magnetos";
  this->numTosim[3] = "/instrumentation/heading-indicator/offset-deg";
  this->numTosim[4] = "/instrumentation/altimeter/indicated-altitude-ft";
  this->numTosim[5] = "/instrumentation/altimeter/pressure-alt-ft";
  this->numTosim[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
  this->numTosim[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
  this->numTosim[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
  this->numTosim[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
  this->numTosim[10] = "/instrumentation/encoder/indicated-altitude-ft";
  this->numTosim[11] = "/instrumentation/encoder/pressure-alt-ft";
  this->numTosim[12] = "/instrumentation/gps/indicated-altitude-ft";
  this->numTosim[13] = "/instrumentation/gps/indicated-ground-speed-kt";
  this->numTosim[14] = "/instrumentation/gps/indicated-vertical-speed";
  this->numTosim[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
  this->numTosim[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
  this->numTosim[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
  this->numTosim[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
  this->numTosim[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
  this->numTosim[20] = "/controls/flight/aileron";
  this->numTosim[21] = "/controls/flight/elevator";
  this->numTosim[22] = "/controls/flight/rudder";
  this->numTosim[23] = "/controls/flight/flaps";
  this->numTosim[24] = "/controls/engines/engine/throttle";
  this->numTosim[25] = "/controls/engines/current-engine/throttle";
  this->numTosim[26] = "/controls/switches/master-avionics";
  this->numTosim[27] = "/controls/switches/starter";
  this->numTosim[28] = "/engines/active-engine/auto-start";
  this->numTosim[29] = "/controls/flight/speedbrake";
  this->numTosim[30] = "/sim/model/c172p/brake-parking";
  this->numTosim[31] = "/controls/engines/engine/primer";
  this->numTosim[32] = "/controls/engines/current-engine/mixture";
  this->numTosim[33] = "/controls/switches/master-bat";
  this->numTosim[34] = "/controls/switches/master-alt";
  this->numTosim[35] = "/engines/engine/rpm";
}

void OpenServerCommand::readFromClient(int client_socket,
                                       int server_socket,
                                       Globals *glob,
                                       unordered_map<string, Data *> *sim_table,
                                       unordered_map<int, string> *numTosim) {

  char buffer[1024] = {0};
  char *p = buffer;
  while (!glob->to_close) {
    this_thread::sleep_for(std::chrono::milliseconds(10));
    int valread = read(client_socket, buffer, 1024);
    char *end = buffer;
    for (int i = 0; i < 36; i++) {
      if (glob->to_close) break;
      if (sim_table->find((*numTosim)[i]) == sim_table->end()) {
        strtod(end, &end);
        end++;
        continue;
      }
      glob->locker.lock();
      (*sim_table)[(*numTosim)[i]]->setValue(strtod(end, &end));
      glob->locker.unlock();
      end++;
    }
  }
  close(server_socket);
}

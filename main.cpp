#include <vector>
#include <unordered_map>
#include "Command.h"
#include "Lexer.h"
#include "Data.h"
#include "OpenServerCommand.h"
#include <queue>
#include "ClientConnectCommand.h"
//
using namespace std;
void parse(vector<string> &, unordered_map<string, Command *> &);
void commandMapInit(unordered_map<string, Command *> *,
                    unordered_map<string, Data *> *,
                    unordered_map<string, Data *> *,
                    queue<string> *);
int main(int argc, char *argv[]) {
  Lexer lex(argv[1]);
  vector<string> string_vec;
  if (!lex.lexer(&string_vec)) {
    cout << "error - can't open fly.txt" << endl;
    exit(1);
  }
  queue<string> update_simulator_q;
  unordered_map<string, Command *> command_map;
  unordered_map<string, Data *> symbol_table;
  unordered_map<string, Data *> sim_table;
  commandMapInit(&command_map, &symbol_table, &sim_table, &update_simulator_q);
  parse(string_vec, command_map);
}
void commandMapInit(unordered_map<string, Command *> *command_map, unordered_map<string, Data *> *symbol_table,
                    unordered_map<string, Data *> *sim_table, queue<string> *update_simulator_q) {
  // here we should initialize all of the commands object and assigned it to the map
  // strings and objects: openDataServer - OpenServerCommand, connectControlClient- ClientConnectCommand,
  // var - CreateVariableCommand , Print - PrintCommand, Sleep - SleepCommand, While/if/function/Condition parser
  //Command *server = new OpenServerCommand(sim_table);
  //string str = "(5400)";
  //server->execute(&str);

  Command *client = new ClientConnectCommand(symbol_table, update_simulator_q);
  client->execute(new string("(\"127.0.0.1\",5402)"));
  Data *d = new Data("/controls/flight/rudder", 1);
  d->setValue(0);
  symbol_table->insert({string("rudder"), d});
  update_simulator_q->push(string("rudder"));
  sleep(5);
  d->setValue(-1);
  update_simulator_q->push(string("rudder"));
  sleep(5);
  d->setValue(1);
  update_simulator_q->push(string("rudder"));
  while(true){}
}
void parse(vector<string> &string_vec, unordered_map<string, Command *> &command_map) {
  for (int i = 0; i < string_vec.size(); i += 2) {
    Command *c = command_map[string_vec[i]];
    if (c) {
      c->execute(&(string_vec[i + 1]));
    }
  }
}
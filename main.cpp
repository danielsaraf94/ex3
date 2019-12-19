#include <vector>
#include <unordered_map>
#include "Command.h"
#include "Lexer.h"
#include "Data.h"
#include "OpenServerCommand.h"
#include <queue>
#include "ClientConnectCommand.h"
#include "Globals.h"
#include "PrintCommand.h"
#include "Var.h"
#include "SleepCommand.h"
//
using namespace std;
void parse(vector<string> &, unordered_map<string, Command *> &);
void commandMapInit(unordered_map<string, Command *> *,
                    unordered_map<string, Data *> *,
                    unordered_map<string, Data *> *,
                    queue<string> *, Globals *);
int main(int argc, char *argv[]) {
  Globals g;
  g.to_close = false;
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
  commandMapInit(&command_map, &symbol_table, &sim_table, &update_simulator_q, &g);
  parse(string_vec, command_map);
}
void commandMapInit(unordered_map<string, Command *> *command_map, unordered_map<string, Data *> *symbol_table,
                    unordered_map<string, Data *> *sim_table, queue<string> *update_simulator_q, Globals *globals) {
  // here we should initialize all of the commands object and assigned it to the map
  // strings and objects: openDataServer - OpenServerCommand, connectControlClient- ClientConnectCommand,
  // var - CreateVariableCommand , Print - PrintCommand, Sleep - SleepCommand, While/if/function/Condition parser
  Command *server = new OpenServerCommand(sim_table, globals);
  (*command_map)[string("openDataServer")] = server;
  Command *client = new ClientConnectCommand(symbol_table, update_simulator_q, globals);
  (*command_map)[string("connectControlClient")] = client;
  Command *var_creator = new Var(command_map, symbol_table, sim_table);
  (*command_map)[string("var")] = var_creator;
  Command *print = new PrintCommand();
  (*command_map)[string("Print")] = print;
  Command *sleep = new SleepCommand();
  (*command_map)[string("Sleep")] = sleep;

}
void parse(vector<string> &string_vec, unordered_map<string, Command *> &command_map) {
  for (int i = 0; i < string_vec.size(); i += 2) {
    Command *c = command_map[string_vec[i]];
    if (c) {
      c->execute(&(string_vec[i + 1]));
    }
  }
}
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
#include <algorithm>
#include "ConditionParser.h"
#include "WhileCommand.h"

using namespace std;
void varAssign(string &, string &, unordered_map<string, Data *> &, queue<string> &update_simulator_q);
void parse(vector<string> &,
           unordered_map<string, Command *> &,
           unordered_map<string, Data *> &,
           queue<string> &update_simulator_q);
void commandMapInit(unordered_map<string, Command *> *, unordered_map<string, Data *> *,
                    unordered_map<string, Data *> *, queue<string> *, Globals *, vector<string> *);

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
  commandMapInit(&command_map, &symbol_table, &sim_table, &update_simulator_q, &g, &string_vec);
  parse(string_vec, command_map, symbol_table, update_simulator_q);
  g.to_close = true;
}
void commandMapInit(unordered_map<string, Command *> *command_map,
                    unordered_map<string, Data *> *symbol_table,
                    unordered_map<string, Data *> *sim_table,
                    queue<string> *update_simulator_q,
                    Globals *globals,
                    vector<string> *string_vec) {
  // here we should initialize all of the commands object and assigned it to the map
  // strings and objects: openDataServer - OpenServerCommand, connectControlClient- ClientConnectCommand,
  // var - CreateVariableCommand , Print - PrintCommand, Sleep - SleepCommand, While/if/function/Condition parser

  Command *server = new OpenServerCommand(sim_table, globals);

  (*command_map)[string("openDataServer")] = server;

  Command *client = new ClientConnectCommand(symbol_table, update_simulator_q, globals);

  (*command_map)[string("connectControlClient")] = client;

  Command *var_creator = new Var(command_map,symbol_table, sim_table,update_simulator_q);

  (*command_map)[string("var")] = var_creator;

  Command *print = new PrintCommand(symbol_table);

  (*command_map)[string("Print")] = print;

  Command *sleep = new SleepCommand();

  (*command_map)[string("Sleep")] = sleep;

  Command *conPar = new ConditionParser(command_map, symbol_table);

  (*command_map)[string("if")] = conPar;

  Command *while_command = new WhileCommand(command_map, symbol_table, string_vec);

  (*command_map)[string("while")] = while_command;

}
void parse(vector<string> &string_vec,
           unordered_map<string, Command *> &command_map,
           unordered_map<string, Data *> &symbol_table, queue<string> &update_simulator_q) {
  for (int i = 0; i < string_vec.size();) {
    Command *c = command_map[string_vec[i]];
    if (c) {
      i += c->execute(&string_vec, i + 1);
    }
  }
}
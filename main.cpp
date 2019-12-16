#include <vector>
#include <map>
#include "Command.h"
#include "Lexer.h"
#include "Data.h"
#include "OpenServerCommand.h"
#include "ClientConnectCommand.h"
using namespace std;
void parse(vector<string> &, map<string, Command *> &);
void commandMapInit(map<string, Command *> *command_map, map<string, Data *> *, map<string, Data *> *);
int main(int argc, char *argv[]) {
  Lexer lex(argv[1]);
  vector<string> string_vec;
  if (!lex.lexer(&string_vec)) {
    cout << "error - can't open fly.txt" << endl;
    exit(1);
  }
  map<string, Command *> command_map;
  map<string, Data *> symbol_table;
  map<string, Data *> sim_table;
  commandMapInit(&command_map, &symbol_table, &sim_table);
  ClientConnectCommand c(symbol_table);
  c.execute(new string("(\"127.0.0.1\",5402)"));
  char hello[] = "set /controls/engines/current-engine/throttle 1\r\n";
  c.updateServer(reinterpret_cast<string *>(hello));
  c.closeClient();
  parse(string_vec, command_map);
}
void commandMapInit(map<string, Command *> *command_map, map<string, Data *> *symbol_table,
                    map<string, Data *> *sim_table) {
  // here we should initialize all of the commands object and assigned it to the map
  // strings and objects: openDataServer - OpenServerCommand, connectControlClient- ClientConnectCommand,
  // var - CreateVariableCommand , Print - PrintCommand, Sleep - SleepCommand, While/if/function/Condition parser
  Command *openData = new OpenServerCommand(sim_table);
  string str = "(5400)";
  string *str1 = &str;
  openData->execute(str1);

}
void parse(vector<string> &string_vec, map<string, Command *> &command_map) {
  for (int i = 0; i < string_vec.size(); i += 2) {
    Command *c = command_map[string_vec[i]];
    if (c) {
      c->execute(&(string_vec[i + 1]));
    }
  }
}
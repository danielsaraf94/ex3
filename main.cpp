#include <vector>
#include <unordered_map>
#include "Command.h"
#include "Lexer.h"
#include "Globals.h"
#include "CommandManager.h"
//
using namespace std;
void parse(vector<string> &, CommandManager *);

int main(int argc, char *argv[]) {
  Globals g;
  Lexer lex(argv[argc - 1]);
  vector<string> string_vec;
  if (!lex.lexer(&string_vec)) {
    cout << "error - can't open fly.txt" << endl;
    exit(1);
  }
  CommandManager manager{&string_vec, &g};
  // parse the string vector made by file_name.txt
  parse(string_vec, &manager);
  // at the time the program reaching here, all the file.txt command was executed and the program should finish
  // announce other threads that the program is over and they should terminate, wait 2 second till shut down the process
  cout << "closing threads and free memory" << endl;
  g.to_close = true;
  std::this_thread::sleep_for (std::chrono::seconds(2));
}

void parse(vector<string> &string_vec, CommandManager *manger) {
  unordered_map<string, Command *> *command_map = manger->getCommnadMap();
  for (int i = 0; i < (int) string_vec.size();) {
    Command *c = (*command_map)[string_vec[i]];
    if (c) {
      i += c->execute(&string_vec, i + 1);
    } else {
      i = manger->addFuncCommand(i + 1);
    }
  }
}
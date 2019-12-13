#include <vector>
#include <map>
#include "Command.h"
#include "Lexer.h"
using namespace std;
void parse(vector<string> *);
int main(int argc, char *argv[]) {
  map<string, Command *> str_command;
  Lexer lexer{argv[1]};
  vector<string> array;
  lexer.lexer(&array);
  int j =0;
}
void parse(vector<string> array, map<string, Command*> str_command) {
  for (int i = 0; i < array.size(); i += 2) {
    Command *c = str_command[array[i]];
    if (!c) {
      c->execute();
    }
  }
}
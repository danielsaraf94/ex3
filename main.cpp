#include <vector>
#include <unordered_map>
#include "Command.h"
#include "Lexer.h"
#include "Globals.h"
#include "CommandManager.h"

using namespace std;
void parse(vector<string> &,CommandManager*);

int main(int argc, char *argv[]) {
  Globals g;
  Lexer lex(argv[1]);
  vector<string> string_vec;
  if (!lex.lexer(&string_vec)) {
    cout << "error - can't open fly.txt" << endl;
    exit(1);
  }
  CommandManager manager{&string_vec,&g};
  parse(string_vec,&manager);
  g.to_close = true;
  cout<<"closing threads and free memory"<<endl;
  sleep(5);
}

void parse(vector<string> &string_vec,CommandManager* manger) {
  unordered_map<string,Command*>* command_map = manger->getCommnadMap();
  for (int i = 0; i < string_vec.size();) {
    Command *c = (*command_map)[string_vec[i]];
    if (c) {
      i += c->execute(&string_vec, i + 1);
    }
  }
}

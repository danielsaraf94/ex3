//
// Created by daniels on 19/12/2019.

#include "PrintCommand.h"

PrintCommand::PrintCommand(unordered_map<string, Data *> *s, Globals *g) {
  this->symbol_table = s;
  globals = g;
}
int PrintCommand::execute(vector<string> *string_vec, int i) {
  string s = (*string_vec)[i];
  s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
  s.erase(std::remove(s.begin(), s.end(), '('), s.end());
  globals->locker.lock();
  if ((*symbol_table).find(s) != (*symbol_table).end()) {
    Data *d = (*symbol_table)[s];
    globals->locker.unlock();
    cout << d->getValue() << endl;
  } else {
    globals->locker.unlock();
    cout << s << endl;
  }
  return 2;
}
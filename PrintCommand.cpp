//
// Created by daniels on 19/12/2019.

#include "PrintCommand.h"

PrintCommand::PrintCommand(unordered_map<string, Data *> *s) {
  this->symbol_table = s;
}
int PrintCommand::execute(vector<string> *string_vec, int i) {
  string s = (*string_vec)[i];
  Data *d = (*symbol_table)[s];
  if (d) {
    cout << d->getValue() << endl;
  } else {
    cout << s << endl;
  }
  return 2;
}
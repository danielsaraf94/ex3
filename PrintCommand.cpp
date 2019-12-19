//
// Created by daniels on 19/12/2019.


#include "PrintCommand.h"

void PrintCommand::execute(string *s) {
  Data *d = (*symbol_table)[*s];
  if (d) {
    cout << d->getValue() << endl;
  } else {
    cout << *s << endl;
  }
}
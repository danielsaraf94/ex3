
// Created by daniels on 19/12/2019.

#include "PrintCommand.h"

PrintCommand::PrintCommand(unordered_map<string, Data *> *s, Globals *g) {
  this->symbol_table = s;
  globals = g;
}
int PrintCommand::execute(vector<string> *string_vec, int i) {
  string s = (*string_vec)[i];
  // extract all the chars inside the outer Parenthesis
  int start = 0, end = 0, k;
  for (k = 0; k < (int) s.length(); k++) {
    if (s[k] == '(') {
      start = k + 1;
      break;
    }
  }
  for (k += 1; k < (int) s.length(); k++) {
    if (s[k] == ')')
      end = k;
  }
  if (end == 0) {
    cerr << "invalid Print" << endl;
    return 2;
  }
  s = s.substr(start, end - start);
  // check the string contains " char
  if (s.find('\"') != string::npos) {
    // " char found - its a string, extract the string and print it
    int start1 = 0, end1 = 0, j;
    for (j = 0; j < (int) s.length(); j++) {
      if (s[j] == '"') {
        start1 = j + 1;
        break;
      }
    }
    for (j += 1; j < (int) s.length(); j++) {
      if (s[j] == '"')
        end1 = j;
    }
    if (end1 == 0) {
      cerr << "invalid Print" << endl;
      return 2;
    }
    cout << s.substr(start1, end1 - start1) << endl;
  } else {
    // its not a string but an expression, calculate it and print the result
    Data d(globals, symbol_table);
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    cout << d.fromStringToValue(s) << endl;
  }
  return 2;
}
//
// Created by daniels on 19/12/2019.

#include "PrintCommand.h"

PrintCommand::PrintCommand(unordered_map<string, Data *> *s, Globals *g) {
  this->symbol_table = s;
  globals = g;
}
int PrintCommand::execute(vector<string> *string_vec, int i) {
  string s = (*string_vec)[i];
  int start = 0, end = 0, j;
  for (j = 0; j < s.length(); j++) {
    if (s[j] == '(') {
      start = j + 1;
      break;
    }
  }
  for (j += 1; j < s.length(); j++) {
    if (s[j] == ')')
      end = j;
  }
  if (end == 0) {
    cerr << "invalid Print" << endl;
    return 2;
  }
  s = s.substr(start, end - start);
  // check the string contains " char
  if (s.find('\"') != string::npos) {
    // " char found - its a string, extract the string and print it
    int start = 0, end = 0, j;
    for (j = 0; j < s.length(); j++) {
      if (s[j] == '"') {
        start = j + 1;
        break;
      }
    }
    for (j += 1; j < s.length(); j++) {
      if (s[j] == '"')
        end = j;
    }
    if (end == 0) {
      cerr << "invalid Print" << endl;
      return 2;
    }
    cout << s.substr(start, end - start) << endl;
  } else if ((*symbol_table).find(s) != (*symbol_table).end()) { // one variable in the symbol table
    Data *d = (*symbol_table)[s];
    cout << d->getValue() << endl;
  } else {
    // its not a string. print the calculation of the variables
    // make all the two char operator represent as one
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    Data d;
    string s1 = "<=";
    string s2 = "$";
    string s3 = ">=";
    string s4 = "%";
    string s5 = "==";
    string s6 = "^";
    string s7 = "!=";
    string s8 = "&";
    d.replace(s, s1, s2);
    d.replace(s, s3, s4);
    d.replace(s, s5, s6);
    d.replace(s, s7, s8);
    int i = 0, l = 0;
    Interpreter interpreter;
    // extract all the variable out of the string and insert it the the interpreter vars map
    while (i <= (int) s.length()) {
      i = d.getIndexAfterOp(s, l);
      l = d.getIndexBeforeOp(s, i);
      string variable_name = s.substr(i, l - i);
      variable_name.erase(remove(variable_name.begin(), variable_name.end(), ')'), variable_name.end());
      variable_name.erase(remove(variable_name.begin(), variable_name.end(), '('), variable_name.end());
      globals->locker.lock();
      if (this->symbol_table->find(variable_name) == this->symbol_table->end()) {
        globals->locker.unlock();
        i = l + 1;
        continue;
      }
      Data *data = (*this->symbol_table)[variable_name];
      globals->locker.unlock();
      string value_str = std::to_string(data->getValue());
      interpreter.setVariables(variable_name + "=" + value_str);
      i = l + 1;
    }
    // return the original operation representation
    d.replace(s, s2, s1);
    d.replace(s, s4, s3);
    d.replace(s, s6, s5);
    d.replace(s, s8, s7);
    try {
      // try to calculate the expression
      auto *exp = interpreter.interpret(s);
      double newValue = exp->calculate();
      delete (exp);
      cout << newValue << endl;
    } catch (...) {
      cerr << "Something went wrong with the interpretation" << endl;
    }
  }
  return 2;
}
#include "Data.h"

Data::Data(string var,
           string simulator,
           int biding,
           queue<string> *queue,
           unordered_map<string, Data *> *map,
           Globals *g) {
  this->sign = biding;
  this->varName = var;
  this->sim = simulator;
  this->update_simulator_q = queue;
  this->symbol_table = map;
  this->globals = g;
}
int Data::execute(vector<string> *string_vec, int j) {
  string str = (*string_vec)[j];
  string s1 = "<=";
  string s2 = "$";
  string s3 = ">=";
  string s4 = "%";
  string s5 = "==";
  string s6 = "^";
  string s7 = "!=";
  string s8 = "&";
  replace(str, s1, s2);
  replace(str, s3, s4);
  replace(str, s5, s6);
  replace(str, s7, s8);
  int i = 0, l = 0;
  Interpreter interpreter;
  while (i <= str.length()) {
    i = getIndexAfterOp(str, l);
    l = getIndexBeforeOp(str, i);
    string varName = str.substr(i, l - i);
    varName.erase(remove(varName.begin(), varName.end(), ')'), varName.end());
    varName.erase(remove(varName.begin(), varName.end(), '('), varName.end());
    globals->locker.lock();
    if (this->symbol_table->find(varName) == this->symbol_table->end()) {
      globals->locker.unlock();
      i = l + 1;
      continue;
    }
    Data *data = (*this->symbol_table)[varName];
    globals->locker.unlock();
    string value = std::to_string(data->getValue());
    interpreter.setVariables(varName + "=" + value);
    i = l + 1;
  }
  replace(str, s2, s1);
  replace(str, s4, s3);
  replace(str, s6, s5);
  replace(str, s8, s7);
  try {
    string expression = str.substr(1);
    double newValue = interpreter.interpret(expression)->calculate();
    setValue(newValue);
  } catch (...) {
    cerr << "Something went wrong with the interpretation" << endl;
  }
  return 2;
}
int Data::getIndexBeforeOp(string str, int i) {
  for (; i < str.length(); i++) {
    if (str[i] == '=' || str[i] == '<' || str[i] == '>' || str[i] == '/' || str[i] == '*' || str[i] == '+'
        || str[i] == '-' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '&') {
      break;
    }
  }
  return i;
}
int Data::getIndexAfterOp(string str, int i) {
  for (; i < str.length(); i++) {
    if (!(str[i] == '=' || str[i] == '<' || str[i] == '>' || str[i] == '/' || str[i] == '*' || str[i] == '+'
        || str[i] == '-' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '&')) {
      break;
    }
  }
  return i;
}
void Data::setValue(double val) {
  this->value = val;
  if (sign == 1) {
    globals->locker.lock();
    this->update_simulator_q->push(this->varName);
    globals->locker.unlock();
  }
}
double Data::getValue() {
  return this->value;
}
string Data::getSim() {
  return this->sim;
}
string Data::getVarName() {
  return this->varName;
}
int Data::getSign() {
  return this->sign;
}
bool Data::replace(std::string &str, const std::string &from, const std::string &to) {
  size_t start_pos = str.find(from);
  if (start_pos == std::string::npos)
    return false;
  str.replace(start_pos, from.length(), to);
  return true;
}
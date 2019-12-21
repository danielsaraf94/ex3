//
// Created by shlomo on 20/12/2019.
//

#include <regex>
#include "ConditionParser.h"
ConditionParser::ConditionParser(unordered_map<string, Command *> *map1, unordered_map<string, Data *> *map2,Globals* g) {
  this->command_map = map1;
  this->symbol_table = map2;
  this->globals=g;
}

int ConditionParser::execute(vector<string> *string_vec, int i) {
  int return_index = returnIndex(string_vec, i) - i;
  int first_index = i - 1;
  if (isTrue((*string_vec)[i])) {
    i++;
    while (i < first_index + return_index - 1) {
      Command *c = (*command_map)[(*string_vec)[i]];
      i += c->execute(string_vec, i + 1);
    }
  }
  return return_index + 1;
}

int ConditionParser::returnIndex(vector<string> *string_vec, int i) {

  while ((int)(*string_vec)[i].find("{") == -1) {
    i++;
  }
  this->q.push("{");
  i++;
  while (!this->q.empty()) {
    if ((int)(*string_vec)[i].find("{") != -1) {
      this->q.push("{");
    }
    if ((int)(*string_vec)[i].find("}") != -1) {
      this->q.pop();
    }
    i++;
  }
  return i;
}
bool ::ConditionParser::isTrue(string str) {
  Data d;
  string s1 = "<=";
  string s2 = "$";
  string s3 = ">=";
  string s4 = "%";
  string s5 = "==";
  string s6 = "^";
  string s7 = "!=";
  string s8 = "&";
  d.replace(str, s1, s2);
  d.replace(str, s3, s4);
  d.replace(str, s5, s6);
  d.replace(str, s5, s6);
  d.replace(str, s7, s8);
  int i = 0, l = 0;
  Interpreter interpreter;
  while (i <= (int)str.length()) {
    i = d.getIndexAfterOp(str, l);
    l = d.getIndexBeforeOp(str, i);
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
  d.replace(str, s2, s1);
  d.replace(str, s4, s3);
  d.replace(str, s6, s5);
  d.replace(str, s8, s7);
  try {
    string expression = str.substr(0);
    expression.erase(remove(expression.begin(), expression.end(), '{'), expression.end());
    auto *exp = interpreter.interpret(expression);
    int result = exp->calculate();
    delete(exp);
    return result;
  } catch (...) {
   cerr << "Something went wrong with the interpretation" << endl;
    return false;
  }
}
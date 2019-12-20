//
// Created by shlomo on 20/12/2019.
//

#include <regex>
#include "ConditionParser.h"
ConditionParser::ConditionParser(unordered_map<string, Command *> *map1, unordered_map<string, Data *> *map2) {
  this->command_map = map1;
  this->symbol_table = map2;
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

  while ((*string_vec)[i].find("{") == -1) {
    i++;
  }
  this->q.push("{");
  i++;
  while (!this->q.empty()) {
    if ((*string_vec)[i].find("{") != -1) {
      this->q.push("{");
    }
    if ((*string_vec)[i].find("}") != -1) {
      this->q.pop();
    }
    i++;
  }
  return i;
}
bool ::ConditionParser::isTrue(string s) {
  string left, right, oper;
  double l, r;
  int i = 0, len = 0;
  // extract the left expression,right expression and operator
  for (; s[len] != '<' && s[len] != '>' && s[len] != '=' && s[len] != '!'; len++) {}
  left = s.substr(i, len);
  i = len;
  for (; s[len] == '<' || s[len] == '>' || s[len] == '=' || s[len] == '!' || s[len] == ' '; len++) {}
  oper = s.substr(i, len - i);
  i = len;
  right = s.substr(i, s.length() - i);
  left.erase(remove(left.begin(), left.end(), ' '), left.end());
  left.erase(remove(left.begin(), left.end(), '('), left.end());
  oper.erase(remove(oper.begin(), oper.end(), ' '), oper.end());
  right.erase(remove(right.begin(), right.end(), ' '), right.end());
  right.erase(remove(right.begin(), right.end(), ')'), right.end());
  right.erase(remove(right.begin(), right.end(), '{'), right.end());
  regex rg("^[-+]?[0-9]+(\\.[0-9]+)?$");
  if (regex_match(left.begin(), left.end(), rg))
    l = stod(left);
  else {
    Data *d = (*this->symbol_table)[left];
    if (d) {
      l = d->getValue();
    } else {
      cout << "bad condition" << endl;
      exit(1);
    }
  }
  if (regex_match(right.begin(), right.end(), rg))
    r = stod(right);
  else {
    Data *d = (*this->symbol_table)[right];
    if (d) {
      r = d->getValue();
    } else {
      cout << "bad condition" << endl;
      exit(1);
    }
  }

  if (oper == "<") { return l < r; }
  else if (oper == "<=") { return l <= r; }
  else if (oper == ">") { return l > r; }
  else if (oper == ">=") { return l >= r; }
  else if (oper == "==") { return l == r; }
  else if (oper == "!=") { return l != r; }
  else return false;
}
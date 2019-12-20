//
// Created by daniels on 20/12/2019.
//

#include <regex>
#include "WhileCommand.h"
WhileCommand::WhileCommand(unordered_map<string, Command *> *c_m, unordered_map<string, Data *> *s_t)
    : c_m(c_m), s_t(s_t) {
}
int WhileCommand::execute(vector<string> *string_vec, int i) {
  string condition = (*string_vec)[i + 1];
  Command *c=(*c_m)["ConditionParser"];
  while (isTrue(condition)) {

  }
}


bool WhileCommand::isTrue(string s) {
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
  oper.erase(remove(oper.begin(), oper.end(), ' '), oper.end());
  right.erase(remove(right.begin(), right.end(), ' '), right.end());
  regex rg("^[-+]?[0-9]+(\\.[0-9]+)?$");
  if (regex_match(left.begin(), left.end(), rg))
    l = stod(left);
  else {
    Data *d = (*s_t)[left];
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
    Data *d = (*s_t)[right];
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

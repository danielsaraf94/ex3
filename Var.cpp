//
// Created by shlomo on 13/12/2019.
//

#include "Var.h"
Var::Var(map<string, Command *> *map1, map<string, Data *> *map2, map<string, Data *> *map3) {
  this->str_command_map = map1;
  this->varName_data_map = map2;
  this->sim_data_map = map3;
}
void Var::execute(string *str) {
  int index = 0;
  int sign = getSign(str, &index);
  string varName = str->substr(0, index);
  Data *data;
  if (sign == 3) {
    string otherVar = str->substr(index + 3, str->length());
    double value = (*this->varName_data_map)[otherVar]->getValue();
    data = new Data("", sign);
    data->setValue(value);
  } else {
    string sim = str->substr(index + 4, str->length());
    data = new Data(sim, sign);
    if (sign == 1) {
      (*this->varName_data_map)[varName] = data;
    } else {
      (*this->sim_data_map)[sim] = data;
    }
  }
  (*this->str_command_map)[varName] = data;
}

int Var::getSign(string *str, int *index) {
  int i = 0;
  size_t found = str->find("->");
  if (found != string::npos) {
    *index = found - 1;
    i = 1;
  }
  found = str->find("<-");
  if (found != string::npos) {
    *index = found - 1;
    i = 2;
  }
  found = str->find("=");
  if (found != string::npos) {
    *index = found - 1;
    i = 3;
  }
  return i;
}

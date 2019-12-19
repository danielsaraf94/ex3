//
// Created by shlomo on 13/12/2019.


#include "Var.h"
Var::Var(
    unordered_map<string, Data *> *map1,
    unordered_map<string, Data *> *map2) {
  this->varName_data_map = map1;
  this->sim_num_map = map2;
}
void Var::execute(string *str) {
  int index = 0;
  int sign = getSign(str, &index);
  string varName = str->substr(0, index);
  Data *data;
  if (sign == 3) {
    string otherVar = str->substr(index + 1, str->length());
    double value = (*this->varName_data_map)[otherVar]->getValue();
    data = new Data("", sign);
    data->setValue(value);
  } else {
    string sim = str->substr(index + 3, str->length());
    data = new Data(sim, sign);
    if (sign == 1) {
      (*this->varName_data_map)[varName] = data;
    } else {
      (*this->sim_num_map)[sim] = data;
    }
  }
}

int Var::getSign(string *str, int *index) {
  int i = 0;
  int found = str->find("->");
  if (found > -1) {
    *index = found;
    i = 1;
  }
  found = str->find("<-");
  if (found > -1) {
    *index = found;
    i = 2;
  }
  found = str->find("=");
  if (found > -1) {
    *index = found;
    i = 3;
  }
  return i;
}
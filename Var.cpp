//
// Created by shlomo on 13/12/2019.


#include "Var.h"
Var::Var(unordered_map<string, Command *> *map1,
         unordered_map<string, Data *> *map2,
         unordered_map<string, Data *> *map3,
         queue<string> *queue) {
  this->str_command_map = map1;
  this->varName_data_map = map2;
  this->sim_num_map = map3;
  this->update_simulator_q = queue;
}
int Var::execute(vector<string> *string_vec, int i) {
  string *str = &(*string_vec)[i];
  int index = 0;
  int sign = getSign(str, &index);
  string varName = str->substr(0, index);
  Data *data;
  if (sign == 3) {
    string otherVar = str->substr(index + 1, str->length());
    double value = (*this->varName_data_map)[otherVar]->getValue();
    data = new Data(varName, "", sign, this->update_simulator_q, this->varName_data_map);
    data->setValue(value);
  } else {
    string sim = str->substr(index + 2, str->length()-1);
    data = new Data(varName, sim, sign, this->update_simulator_q, this->varName_data_map);
    if (sign == 2) {
      (*this->sim_num_map)[sim] = data;
    }
  }
  (*this->varName_data_map)[varName] = data;
  (*this->str_command_map)[varName] = data;
  return 2;
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
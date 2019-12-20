
#include "Var.h"
Var::Var(unordered_map<string, Command *> *map1,
         unordered_map<string, Data *> *map2,
         unordered_map<string, Data *> *map3,
         queue<string> *queue,Globals* g) {
  this->str_command_map = map1;
  this->varName_data_map = map2;
  this->sim_num_map = map3;
  this->update_simulator_q = queue;
  this->globals=g;
}
int Var::execute(vector<string> *string_vec, int i) {
  string *str = &(*string_vec)[i];
  int index = 0;
  int sign = getSign(str, &index);
  string varName = str->substr(0, index);
  Data *data;
  globals->locker.lock();
  if (sign == 3) {
    string otherVar = str->substr(index + 1, str->length());
    double value = (*this->varName_data_map)[otherVar]->getValue();
    data = new Data(varName, "", sign, this->update_simulator_q, this->varName_data_map,globals);
    data->setValue(value);
  } else {
    string sim = str->substr(index + 2, str->length());
    sim.erase(std::remove_if(sim.begin(), sim.end(), &Var::isParentheses), sim.end());
    data = new Data(varName, sim, sign, this->update_simulator_q, this->varName_data_map,globals);
    if (sign == 2) {
      (*this->sim_num_map)[sim] = data;
    }
  }
  (*this->varName_data_map)[varName] = data;
  (*this->str_command_map)[varName] = data;
  globals->locker.unlock();
  return 2;
}
bool Var::isParentheses(char c) {
  switch (c) {
    case '(':
    case ')':return true;
    default:return false;
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
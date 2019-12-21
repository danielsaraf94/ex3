#include "Var.h"
Var::Var(unordered_map<string, Command *> *map1,
         unordered_map<string, Data *> *map2,
         unordered_map<string, Data *> *map3,
         queue<string> *queue, Globals *g) {
  this->str_command_map = map1;
  this->varName_data_map = map2;
  this->sim_num_map = map3;
  this->update_simulator_q = queue;
  this->globals = g;
}
int Var::execute(vector<string> *string_vec, int i) {
  string *str = &(*string_vec)[i];
  int index = 0;
  // check the update direction
  int sign = getSign(str, &index);
  string varName = str->substr(0, index);
  Interpreter inter;
  // check if the name is valid
  try {
    inter.setVariables(varName + "=0");
  } catch (...) {
    cerr << "bad variable's name input" << endl;
    exit(1);
  }
  Data *data;
  // create the Data object
  if (sign == 3) {
    string otherVar = str->substr(index + 1, str->length());
    globals->locker.lock();
    data = new Data(varName, "", sign, this->update_simulator_q, this->varName_data_map, globals);
    globals->locker.unlock();
    data->execute(string_vec, i);
  } else {
    string sim = str->substr(index + 2, str->length());
    sim.erase(std::remove_if(sim.begin(), sim.end(), &Var::isParentheses), sim.end());
    globals->locker.lock();
    data = new Data(varName, sim, sign, this->update_simulator_q, this->varName_data_map, globals);
    globals->locker.unlock();
    if (sign == 2) {
      globals->locker.lock();
      (*this->sim_num_map)[sim] = data;
      globals->locker.unlock();
    }
  }
  // insert to the maps
  globals->locker.lock();
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
// check the update direction
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

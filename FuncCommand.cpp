
#include "FuncCommand.h"
FuncCommand::FuncCommand(vector<string> *vector, int i, CommandManager *m, Globals *g) {
  this->string_vec = vector;
  this->index = i;
  this->manager = m;
  this->args = false;
  this->globals = g;
}
int FuncCommand::execute(vector<string> *vector, int i) {
  unordered_map<string, Command *> *command_map = manager->getCommnadMap();
  unordered_map<string, Data *> *symbol_map = manager->getSymbolMap();
  unordered_map<string, Data *> *sim_map = manager->getSimMap();
  string varName;
  int otherVarSign = 3;
  Data *otherVar;
  //if there is an argument we add its value
  int j = i;
  i = this->index;
  if (args) {
    varName = (*vector)[index];
    (*vector)[index] += "=" + (*vector)[j];
    i--;
    otherVar = (*symbol_map)[varName];
    if (otherVar) {
      otherVarSign = otherVar->getSign();
      if (otherVarSign == 2) {
        sim_map->erase(varName);
      }
      command_map->erase(varName);
      globals->locker.lock();
      symbol_map->erase(varName);
      globals->locker.unlock();
    }

  }
  //execute all the commands in the func scope
  while (i < return_index - 1) {
    Command *c = (*command_map)[(*string_vec)[i]];
    i += c->execute(string_vec, i + 1);
  }
  //if there is arguments
  if (args) {
    (*vector)[index] = varName;
    Data *com = (*symbol_map)[varName];
    int sign = com->getSign();
    if (sign == 2) {
      sim_map->erase(varName);
    }
    delete (com);
    command_map->erase(varName);
    globals->locker.lock();
    symbol_map->erase(varName);
    globals->locker.unlock();
    if (otherVar) {
      (*command_map)[varName] = otherVar;
      globals->locker.lock();
      (*symbol_map)[varName] = otherVar;
      globals->locker.unlock();
      if (otherVarSign == 2) {
        (*sim_map)[varName] = otherVar;
      }
    }
  }
  return 2;
}
//a bool that tells if the func has arguments
void FuncCommand::setArgs() {
  this->args = true;
}
//change the first index of the function
void FuncCommand::setIndex(int i) {
  this->index = i;
}
//the index that need to be return after the deceleration of the function
int FuncCommand::returnIndex() {
  int i = this->index;
  queue<string> q;
  //the index is calculated by the braces
  while ((int) (*string_vec)[i].find("{") == -1) {
    i++;
  }
  q.push("{");
  i++;
  while (!q.empty()) {
    if ((int) (*string_vec)[i].find("{") != -1) {
      q.push("{");
    }
    if ((int) (*string_vec)[i].find("}") != -1) {
      q.pop();
    }
    i++;
  }
  this->return_index = i;
  return i;
}
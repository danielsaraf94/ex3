//
// Created by shlomo on 21/12/2019.
//

#include "FuncCommand.h"
FuncCommand::FuncCommand(vector<string> *vector, int i, CommandManager *m) {
  this->string_vec = vector;
  this->index = i;
  this->manager = m;
  this->args = false;
}
int FuncCommand::execute(vector<string> *vector, int i) {
  unordered_map<string, Command *> *command_map = manager->getCommnadMap();
  string varName;
  //if there is an argument we add its value
  if (args) {
    varName = (*vector)[index];
    (*vector)[index] += "=" + (*vector)[i];
    i = this->index - 1;
  }
  //execute all the commands in the func scope
  while (i < return_index - 1) {
    Command *c = (*command_map)[(*string_vec)[i]];
    i += c->execute(string_vec, i + 1);
  }
  if (args) {
    (*vector)[index] = varName;
    Command *com = (*command_map)[varName];
    delete (com);
    command_map->erase(varName);
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

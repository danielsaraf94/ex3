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

  if (args) {
    (*vector)[index] +="="+(*vector)[i];
    i = this->index-1;
  }
  // if the condition is true - execute all the commands in the if scope
  while (i < return_index - 1) {
    Command *c = (*command_map)[(*string_vec)[i]];
    i += c->execute(string_vec, i + 1);
  }
  return 2;
}
void FuncCommand::setArgs() {
  this->args = true;
}
void FuncCommand::setIndex(int i){
  this->index = i;
}
int FuncCommand::returnIndex() {
  int i = this->index;
  queue<string> q;
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

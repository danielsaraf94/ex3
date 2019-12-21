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
  //calculate how much indexes to move forward when return from execute
  unordered_map<string, Command *> *command_map = manager->getCommnadMap();

  if (args) {
    (*vector)[index + 1] += (*vector)[i];
  }
  i = this->index;
  int first_index = i - 1;
  i++;
  // if the condoion is true - execute all the commands in the if scope
  while (i < first_index + return_index - 1) {
    Command *c = (*command_map)[(*string_vec)[i]];
    i += c->execute(string_vec, i + 1);
  }
  return 2;
}
void FuncCommand::setArgs() {
  this->args = true;
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

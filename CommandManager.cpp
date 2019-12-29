//
// Created by shlomo on 21/12/2019.
//

#include "CommandManager.h"
#include "FuncCommand.h"
CommandManager::CommandManager(vector<string> *vector, Globals *g) {
  this->string_vec = vector;
  this->globals = g;
  initializeCommandMap();
}
void CommandManager::initializeCommandMap() {
  // initialize all the command and insert it to command map
  Command *server = new OpenServerCommand(&sim_table, globals,&symbol_table);

  command_map[string("openDataServer")] = server;

  Command *client = new ClientConnectCommand(&symbol_table, &update_simulator_q, globals);

  command_map[string("connectControlClient")] = client;

  Command *var_creator = new Var(&command_map, &symbol_table, &sim_table, &update_simulator_q, globals);

  command_map[string("var")] = var_creator;

  Command *print = new PrintCommand(&symbol_table, globals);

  command_map[string("Print")] = print;

  Command *sleep = new SleepCommand( &symbol_table, globals);

  command_map[string("Sleep")] = sleep;

  Command *conPar = new ConditionParser(&command_map, &symbol_table, globals);

  command_map[string("if")] = conPar;

  Command *while_command = new WhileCommand(&command_map, string_vec, &symbol_table, globals);

  command_map[string("while")] = while_command;
}
unordered_map<string, Command *> *CommandManager::getCommnadMap() {
  return &this->command_map;
}
unordered_map<string, Data *> *CommandManager::getSymbolMap() {
  return &this->symbol_table;
}
unordered_map<string, Data *> *CommandManager::getSimMap() {
  return &this->sim_table;
}
int CommandManager::addFuncCommand(int index) {
  // when find a new function, add it to the command table
  FuncCommand *func = new FuncCommand(this->string_vec, index, this, globals);
  command_map[(*this->string_vec)[index - 1]] = func;
  int returnVal = func->returnIndex();
  int varLoc = (*this->string_vec)[index].find("var");
  if (varLoc > -1) {
    string variable_name = (*this->string_vec)[index].substr(4);
    variable_name.erase(remove(variable_name.begin(), variable_name.end(), ')'), variable_name.end());
    variable_name.erase(remove(variable_name.begin(), variable_name.end(), '{'), variable_name.end());
    (*string_vec)[index - 1] = "var";
    (*string_vec)[index] = variable_name;
    func->setArgs();
  } else {
    func->setIndex(index + 1);
  }
  return returnVal;
}
// delete all the allocated memory
CommandManager::~CommandManager() {
  for (pair<string, Command *> p : this->command_map) {
    Command *c = p.second;
    if (c)
      delete (c);
  }
}
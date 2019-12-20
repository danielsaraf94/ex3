//
// Created by shlomo on 12/12/2019.
//
#include <fstream>
#include "Lexer.h"
#include <sstream>

Lexer::Lexer(string name) {
  this->file_name = name;
}

bool Lexer::lexer(vector<string> *vector) {
  ifstream input_file;
  input_file.open(this->file_name, ifstream::in);
  if (!input_file) {
    cerr << "Cannot open file: " << this->file_name << endl;
    return false;
  }
  string line;
  while (getline(input_file, line)) {
    if(line==""){
      continue;
    }
    int i = separationLoc(line);
    string command = line.substr(0, i);
    command.erase(std::remove_if(command.begin(), command.end(), &isParenthesesOrApos), command.end());
    command.erase(std::remove_if(command.begin(), command.end(), &isSpace), command.end());
    command.erase(std::remove_if(command.begin(), command.end(), &isSpace), command.end());
    command.erase(std::remove(command.begin(), command.end(), '\t'), command.end());
    vector->push_back(command);
    if (i != line.length()) {
      string args = line.substr(i, line.length());
      if (command != "Print") {
        args.erase(std::remove_if(args.begin(), args.end(), &Lexer::isSpace), args.end());
      }
      args.erase(std::remove_if(args.begin(), args.end(), &Lexer::isParenthesesOrApos), args.end());
      int simLoc = args.find("sim");
      if (simLoc > -1) {
        args = args.substr(0, simLoc) + args.substr(simLoc + 3);
      }
      args.erase(std::remove(args.begin(), args.end(), '\t'), args.end());
      vector->push_back(args);
    }
  }
  input_file.close();
  return true;
}
int Lexer::separationLoc(string &str) {
  bool flag = false;
  for (int i = 1; i < str.length(); i++) {
    char c = str[i];
    if (c != ' ') {
      flag = true;
    }
    if ((c == ' ' && flag) || c == '(' || c == '=' || c == '>' || c == '<' || c == '+' || c == '/' || c == '*'
        || c == '-') {
      return i;
    }
  }
}
bool Lexer::isParenthesesOrApos(char c) {
  switch (c) {
    case '(':
    case ')':
    case '"':return true;
    default:return false;
  }
}
bool Lexer::isSpace(char c) {
  if (c == ' ') {
    return true;
  }
  return false;
}
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
    int i = line.find("(");
    int j = line.find(" ");
    if (i == -1) {
      i = line.length();
    }
    if (j < i && j != -1) {
      i = j + 1;
    }
    string command = line.substr(0, i);
    command.erase(std::remove_if(command.begin(), command.end(), &isParenthesesOrApos), command.end());
    command.erase(std::remove_if(command.begin(), command.end(), &isSpace), command.end());
    vector->push_back(command);
    if (i != line.length()) {
      string args = line.substr(i, line.length());
      if(command!="Print"){
        args.erase(std::remove_if(args.begin(), args.end(), &Lexer::isSpace), args.end());
      }
      args.erase(std::remove_if(args.begin(), args.end(), &Lexer::isParenthesesOrApos), args.end());
      int simLoc = args.find("sim");
      if (simLoc > -1) {
        args = args.substr(0, simLoc) + args.substr(simLoc + 3);
      }
      vector->push_back(args);
    }
  }
  input_file.close();
  return true;
}
bool Lexer::isParenthesesOrApos(char c) {
  switch (c) {
    case '(':
    case ')':
    case '"':return true;
    default:return false;
  }
}
bool Lexer:: isSpace(char c){
  if(c==' '){
    return true;
  }
  return false;
}
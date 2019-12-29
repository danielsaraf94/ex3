//
// Created by shlomo on 12/12/2019.

#include <fstream>
#include "Lexer.h"
#include <sstream>

Lexer::Lexer(string name) {
  this->file_name = name;
}
//the lexer separate the text into sequence of command - arguments
bool Lexer::lexer(vector<string> *vector) {
  ifstream input_file;
  input_file.open(this->file_name, ifstream::in);
  if (!input_file) {
    cerr << "Cannot open file: " << this->file_name << endl;
    return false;
  }
  string line;
  //reading line after line from the text
  while (getline(input_file, line)) {
    if (line == "") {
      continue;
    }

    int i = separationLoc(line);
    //the separate location in the line to command - args according to i
    string command = line.substr(0, i);
    //some manipulate on the string command
    command.erase(std::remove_if(command.begin(), command.end(), &isApos), command.end());
    command.erase(std::remove_if(command.begin(), command.end(), &isSpace), command.end());
    command.erase(std::remove(command.begin(), command.end(), '\t'), command.end());
    vector->push_back(command);
    if (i != (int) line.length()) {
      string args = line.substr(i, line.length());
      //the print command is a special case when we do want to remove the spaces and the ""
      if (command != "Print") {
        args.erase(std::remove_if(args.begin(), args.end(), &Lexer::isSpace), args.end());
        args.erase(std::remove_if(args.begin(), args.end(), &Lexer::isApos), args.end());
      }
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
//return the index of the separate location of the line to command - args
int Lexer::separationLoc(string &str) {
  bool flag = false;
  int i;
  for (i = 1; i < (int) str.length(); i++) {
    char c = str[i];
    if (c != ' ') {
      flag = true;
    }
    if ((c == ' ' && flag) || c == '(' || c == '=' || c == '>' || c == '<' || c == '+' || c == '/' || c == '*'
        || c == '-') {
      break;
    }
  }
  return i;
}
//helper to the remove if
bool Lexer::isApos(char c) {
    return (c=='"');
}
//helper to the remove if
bool Lexer::isSpace(char c) {
  return (c==' ');
}
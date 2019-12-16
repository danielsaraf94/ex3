//
// Created by shlomo on 12/12/2019.
//shlomo

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
      i = j+1;
    }
    string command = line.substr(0, i);
    vector->push_back(command);
    if (i != line.length()) {
      string args = line.substr(i, line.length());
      vector->push_back(args);
    }
  }
  input_file.close();
  return true;
}

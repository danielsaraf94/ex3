//
// Created by shlomo on 04/11/2019.
//

#ifndef EX1_EX1_H
#define EX1_EX1_H
#include <iostream>
#include <map>
#include <regex>
#include <stack>
#include <queue>
#include "Expression.h"

using namespace std;
class Variable : public Expression {
  string name;
  double value;
 public:
  Variable(string, double);
  Variable(Variable *);
  Variable &operator++(int);
  Variable &operator++();
  Variable &operator--(int);
  Variable &operator--();
  Variable &operator+=(double);
  Variable &operator-=(double);
  virtual double calculate();
  virtual ~Variable();
};

class Value : public Expression {
  double value;
 public:
  Value(double);
  double calculate();
  virtual ~Value();
};

class UnaryOperator : public Expression {
 protected:
  Expression *exp;
  UnaryOperator(Expression *);
 public:
  virtual ~UnaryOperator();
};

class BinaryOperator : public Expression {
 protected:
  Expression *left;
  Expression *right;
  BinaryOperator(Expression *, Expression *);
 public:
  virtual ~BinaryOperator();
};

class UPlus : public UnaryOperator {
 public:
  UPlus(Expression *exp);
  virtual ~UPlus();
  double calculate();
};
class UMinus : public UnaryOperator {
 public:
  UMinus(Expression *exp);
  virtual ~UMinus();
  double calculate();
};

class Plus : public BinaryOperator {
 public:
  Plus(Expression *left, Expression *right);
  virtual ~Plus();
  double calculate();
};

class Mul : public BinaryOperator {
 public:
  Mul(Expression *left, Expression *right);
  virtual ~Mul();
  double calculate();
};

class Div : public BinaryOperator {
 public:
  Div(Expression *left, Expression *right);
  virtual ~Div();
  double calculate();
};

class Minus : public BinaryOperator {
 public:
  Minus(Expression *left, Expression *right);
  virtual ~Minus();
  double calculate();
};

class Interpreter {
  std::map<string, double> map;
  std::map<string, int> operatorMap;
  stack<string> s1;
  queue<string> s2;
  stack<Expression *> s3;
  bool checkVar(string);
  bool checkNum(string);
  bool putInStack(string);
  void pushOp(string);
  bool popFromStack();
  int pushNum(string);
  int pushVar(string);
  bool checkStack();
  void startOver();
  Expression *buildExp();
 public:
  Interpreter();
  void setVariables(string);
  Expression *interpret(string);

};

#endif //EX1_EX1_H

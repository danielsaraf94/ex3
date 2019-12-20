//
// Created by daniels on 07/11/2019.
//
#include <cstring>
#include <iostream>
#include <map>
#include <cstdlib>
#include <stack>
#include <queue>
#include <stdexcept>
#include "Expression.h"
#ifndef UNTITLED2_EX1_H
#define UNTITLED2_EX1_H

using namespace std;

class Value : public Expression {

  double val;
 public:
  explicit Value(double x) : val(x) {}

  double calculate() override;

  double getVal() const {
    return val;
  }
};

//----------------------------------------------------------------------------
class Variable : public Expression {
  string name;
  double value;
 public:
  Variable(string n, double v);

  double calculate() override;

  Variable &operator++();

  Variable &operator++(int);

  string getName();

  double getValue() const;

  Variable &operator--();

  Variable &operator--(int);

  Variable &operator+=(double);

  Variable &operator-=(double);

};

//----------------------------------------------------------------------------
class UnaryOperator : public Expression {
 protected:
  Expression *exp = nullptr;

  explicit UnaryOperator(Expression *e) : exp(e) {};
 public:
  ~UnaryOperator() override;
};

//----------------------------------------------------------------------------
class UPlus : public UnaryOperator {
 public:
  explicit UPlus(Expression *e) : UnaryOperator(e) {}

  double calculate() override;
};

//----------------------------------------------------------------------------
class UMinus : public UnaryOperator {
 public:
  explicit UMinus(Expression *e) : UnaryOperator(e) {}

  double calculate() override;
};

//----------------------------------------------------------------------------
class BinaryOperator : public Expression {
 protected:
  Expression *expR = nullptr, *expL = nullptr;

  BinaryOperator(Expression *r, Expression *l) : expR(r), expL(l) {};
 public:
  ~BinaryOperator() override;
};

//----------------------------------------------------------------------------
class Plus : public BinaryOperator {

 public:
  Plus(Expression *r, Expression *l) : BinaryOperator(r, l) {};

  double calculate() override;
};

//----------------------------------------------------------------------------
class Minus : public BinaryOperator {

 public:
  Minus(Expression *r, Expression *l) : BinaryOperator(r, l) {};

  double calculate() override;
};

//----------------------------------------------------------------------------
class Mul : public BinaryOperator {

 public:
  Mul(Expression *r, Expression *l) : BinaryOperator(r, l) {};

  double calculate() override;
};

//----------------------------------------------------------------------------
class Div : public BinaryOperator {

 public:
  Div(Expression *r, Expression *l) : BinaryOperator(r, l) {};

  double calculate() override;
};

//----------------------------------------------------------------------------
class Interpreter {
  map<string, double> vMap;

  void stringToVariable(string s);

  string getLetter(string, int &);

  bool isOperator(string);

  bool isVariable(string);

  bool leftIsPrefer(string, string);
  bool isValidVariableString(string);

  Expression *expressionCreator(queue<string>);

  bool validParenthesis(string);

 public:
  Expression *interpret(string stringExp);

  void setVariables(string);

};

#endif //UNTITLED2_EX1_H
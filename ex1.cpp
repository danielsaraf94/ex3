#include "ex1.h"
//
// Created by shlomo on 04/11/2019.
//

/*
 * the Variable constructor
 * param name - the name of the variable.
 * param value - the value of of the variable
 */
Variable::Variable(string str, double val) {
  this->name = str;
  this->value = val;
}
/*
 * operator overloading in Variable class
 */
Variable &Variable::operator++(int) {
  ++*this;
  return *this;
}
/*
 * operator overloading in Variable class
 */
Variable &Variable::operator++() {
  ++(this->value);
  return *this;
}
/*
 * operator overloading in Variable class
 */
Variable &Variable::operator--(int) {
  --*this;
  return *this;
}
Variable &Variable::operator--() {
  --(this->value);
  return *this;
}
/*
 * operator overloading in Variable class
 */
Variable &Variable::operator+=(double val) {
  this->value = this->value + val;
  return *this;
}
/*
 * operator overloading in Variable class
 */
Variable &Variable::operator-=(double val) {
  this->value = this->value - val;
  return *this;
}
/*
 * Calculate return the value of the varibale
 */
double Variable::calculate() {
  return value;
}
/*
 * Variable destructor
 */
Variable::~Variable() {

}
/*
 * the Value constructor
 * param value - the value
 */
Value::Value(double val) {
  this->value = val;
}
/*
 * Calculate return the value.
 */
double Value::calculate() {
  return this->value;
}
/*
 * value destructor
 */
Value::~Value() {}
/*
 * the UnaryOperator constructor
 * param exp - pointer to the inner class
 */
UnaryOperator::UnaryOperator(Expression *expression) {
  this->exp = expression;
}
/*
 * Unaryoperator destructor
 */
UnaryOperator::~UnaryOperator() {
  if (this->exp != NULL) {
    delete this->exp;
  }
}
/*
 * the BinaryOperator constructor
 * param left - pointer to the inner class
 * param right - pointer to the inner class
 */
BinaryOperator::BinaryOperator(Expression *l, Expression *r) {
  this->left = l;
  this->right = r;
}
/*
 * BinaryOperator destructor
 */
BinaryOperator::~BinaryOperator() {
  if (this->right != NULL) {
    delete this->right;
  }
  if (this->left != NULL) {
    delete this->left;
  }
}
/*
 * the Uplus constructor
 * param exp - pointer to the inner class
 */
UPlus::UPlus(Expression *expression) : UnaryOperator(expression) {}
UPlus::~UPlus() {}

double UPlus::calculate() {
  return this->exp->calculate();
}
/*
 * the Uminus constructor
 * param exp - pointer to the inner class
 */
UMinus::UMinus(Expression *expression) : UnaryOperator(expression) {}
UMinus::~UMinus() {}
double UMinus::calculate() {
  return -1 * (this->exp->calculate());
}
/*
 * the Plus constructor
 * param left - pointer to the inner class
 * param right - pointer to the inner class
 */
Plus::Plus(Expression *l, Expression *r) : BinaryOperator(l, r) {}
Plus::~Plus() {}
/*
 * Calculate return the sum of the two inner claas
 */
double Plus::calculate() {
  return this->left->calculate() + this->right->calculate();
}
/*
 * the Minus constructor
 * param left - pointer to the inner class
 * param right - pointer to the inner class
 */
Minus::Minus(Expression *l, Expression *r) : BinaryOperator(l, r) {}
Minus::~Minus() {}
/*
 * Calculate return the subtraction of the two inner claass
 */
double Minus::calculate() {
  return this->left->calculate() - this->right->calculate();
}
/*
 * the Mul constructor
 * param left - pointer to the inner class
 * param right - pointer to the inner class
 */
Mul::Mul(Expression *l, Expression *r) : BinaryOperator(l, r) {}
Mul::~Mul() {}
/*
 * Calculate return the multiplication of the two inner claas
 */
double Mul::calculate() {
  return this->left->calculate() * this->right->calculate();
}
/*
 * the Div constructor
 * param left - pointer to the inner class
 * param right - pointer to the inner class
 */
Div::Div(Expression *l, Expression *r) : BinaryOperator(l, r) {}
Div::~Div() {}
/*
 * Calculate return the division of the two inner claas
 */
double Div::calculate() {
  if (this->right->calculate() == 0) {
    throw "bad input";
  }
  return this->left->calculate() / this->right->calculate();
}
/*
 * the Interpreter constructor
 * initialize the operator map
 */
Interpreter::Interpreter() {
  this->operatorMap["-"] = 1;
  this->operatorMap["+"] = 1;
  this->operatorMap["*"] = 2;
  this->operatorMap["/"] = 2;
  this->operatorMap["^"] = 3;
  this->operatorMap["&"] = 3;
}
/*
 * checkNum - checks if a certain string is a valid floating ponint
 * str - the certain string
 */
bool Interpreter::checkNum(string str) {
  regex rg("^[-+]?[0-9]+(\\.[0-9]+)?$");
  if (!(regex_match(str.begin(), str.end(), rg))) {
    return false;
  }
  return true;
}
/*
 * checkVar - checks if a certain string is a valid variable
 * str - the certain string
 */
bool Interpreter::checkVar(string var) {
  int i = var.substr(0, var.length()).find('=');
  if (i == -1 || (unsigned) i == var.length() - 1) {
    return false;
  }
  string varName = var.substr(0, i);
  string num = var.substr(i + 1, var.length());
  regex rg("^([a-z]*[A-Z]*_*)+[0-9]*[a-z]*[A-Z]*_*$");
  //verified the string
  if (!(regex_match(varName.begin(), varName.end(), rg))) {
    return false;
  }
  if (!checkNum(num)) {
    return false;
  }
  const char *c = num.c_str();
  double value = atof(c);
  this->map[varName] = value;
  return true;
}
/*
 * setVariables - initialized the variables in the map in order to use them
 * in the interpret process
 * str - the string that contains the variables data
 */
void Interpreter::setVariables(string str) {
  std::string s = str;
  //checks the validity of the string
  if (str[0] == ';' || str[str.length() - 1] == ';') {
    throw "bad input";
  }
  std::vector<std::string> array;
  std::stringstream ss(s);
  std::string tmp;
  //separate the string into several string that each of them contain date of 1 variable
  while (std::getline(ss, tmp, ';')) {
    array.push_back(tmp);
  }
  //checks each variable individually
  for (unsigned int i = 0; i < array.size(); i++) {
    if (!checkVar(array[i])) {
      throw "bad input";
    }
  }
}
/*
 * pushOp - push operator to the stack and verified that the mathematical priority is
 * maintained
 * s - the operator that is being pushed to the stack
 */
void Interpreter::pushOp(string s) {
  string top;
  while (!this->s1.empty()) {
    top += this->s1.top();
    if (!(this->operatorMap[top] > 0)) {
      break;
    }
    // maintain the mathematical priority
    if (this->operatorMap[s] < this->operatorMap[top]) {
      this->s2.push(top);
      this->s1.pop();
    } else {
      break;
    }
    top.clear();
  }
  this->s1.push(s);
}
/*
 * popFromstack - pop all the mathematical expression between the parentheses. after we reach to closing
 * parentheses
 * if the opening parentheses is not in the stack the methoeds return false
 */
bool Interpreter::popFromStack() {
  bool flag = false;
  string top;
  while (!this->s1.empty()) {
    top = this->s1.top();
    this->s1.pop();
    if (top.compare("(") == 0) {
      flag = true;
      break;
    } else {
      this->s2.push(top);
    }
  }
  return flag;
}
/*
 * pushNum - push number to the queue and returns its length.
 *  str - the string that contain the number
 */
int Interpreter::pushNum(string str) {
  unsigned int i;
  string check;
  for (i = 1; i < str.length(); i++) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
      continue;
    } else {
      break;
    }
  }
  check.append(str, 0, i);
  if (!checkNum(check)) {
    return -1;
  }
  this->s2.push(check);
  return i;
}
/*
 * pushVar - push variable to the queue and returns its length.
 *  str - the string that contain the variable
 */
int Interpreter::pushVar(string str) {
  unsigned int i;
  string check;
  for (i = 0; i < str.length(); i++) {
    if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
        || str[i] == '_') {
      continue;
    } else {
      break;
    }
  }
  check.append(str, 0, i);
  if (this->map.count(check) > 0) {
    this->s2.push(check);
    return i;
  }
  return -1;
}
/*
 * verified that the expression that we get is valid and push all the
 * remaining string in the stack to queue.
 */
bool Interpreter::checkStack() {
  while (!this->s1.empty()) {
    if (s1.top().compare("(") == 0) {
      return false;
    }
    this->s2.push(this->s1.top());
    this->s1.pop();
  }
  return true;
}
/*
 * putInstack - gets an expression in string, verified it and puts
 * the string in a queue and stack according to the shunting yard algorithm
 * str - the string that holds the expression.
 * return - true - success , false - failure
 */
bool Interpreter::putInStack(string str) {
  if (str[0] == ')' || str[0] == '*' || str[0] == '/') {
    return false;
  }
  int flagOp = 0, flagNum = 0, flagVar = 0, flagP1 = 0, flagP2 = 0, check;
  string s;
  for (unsigned int i = 0; i < str.length(); i++) {
    s.clear();
    s.append(str, i, 1);
    if (str[i] == '(') {
      if (flagNum || flagVar || flagP2) {
        return false;
      }
      this->s1.push(s);
      flagP1 = 1, flagOp = 0, flagNum = 0, flagP2 = 0, flagVar = 0;
    } else if (str[i] == ')') {
      if (flagOp || flagP1 || !popFromStack()) {
        return false;
      }
      flagP1 = 0, flagOp = 0, flagNum = 0, flagP2 = 1;
    } else if ((!(i != str.length() - 1 && (str[i + 1] >= '0' && str[i] <= '9')) || (flagNum > 0 || flagVar > 0))
        && (this->operatorMap.count(s) > 0)) {
      if (i == 0 || flagP1) {
        if (s.compare("+") == 0) {
          s = "&";
        }
        if (s.compare("-") == 0) {
          s = "^";
        }
        if (s.compare("*") == 0 || s.compare("/") == 0 || flagOp) {
          return false;
        }
      }
      pushOp(s);
      flagP1 = 0, flagOp = 1, flagP2 = 0, flagNum = 0, flagVar = 0;
    } else if ((str[i] >= '0' && str[i] <= '9') || (str[i] == '-' || str[i] == '+')) {
      if (flagVar || flagP2 || (flagOp && (str[i] == '+' || str[i] == '-'))) {
        return false;
      }
      check = pushNum(str.substr(i, str.length()));
      if (check < 0) {
        return false;
      }
      flagP1 = 0, flagOp = 0, flagNum = 1, flagP2 = 0, flagVar = 0;
      i = i + check - 1;
    } else {
      check = pushVar(str.substr(i, str.length()));
      if (check < 0 || flagNum || flagP2) {
        return false;
      }
      if ((flagOp) && (str[i - 1] == '^' || str[i - 1] == '&')) {
        return false;
      }
      i = i + check - 1;
      flagP1 = 0, flagOp = 0, flagNum = 0, flagP2 = 0, flagVar = 1;
    }
  }
  return checkStack();
}
/*
 * buldExp - build Expression according to data in the queue
 * and according to shunting yard algorithm
 */
Expression *Interpreter::buildExp() {
  string str;
  Expression *e1 = nullptr, *e2 = nullptr;
  //in this loop a string is poped from the queue and goes to the expression stack according to its value
  while (!this->s2.empty()) {
    str.clear();
    str += this->s2.front();
    this->s2.pop();
    if (checkNum(str)) {
      const char *c = str.c_str();
      double value = atof(c);
      this->s3.push(new Value(value));
    } else if (this->map.count(str) > 0) {
      this->s3.push(new Variable(str, this->map[str]));
    } else if (this->operatorMap.count(str) > 0 && (str.compare("&") != 0 && str.compare("^") != 0)) {
      if (s3.size() < 2) {
        return nullptr;
      }
      e2 = this->s3.top();
      this->s3.pop();
      e1 = this->s3.top();
      this->s3.pop();
      if (str.compare("*") == 0) {
        this->s3.push(new Mul(e1, e2));
      } else if (str.compare("/") == 0) {
        this->s3.push(new Div(e1, e2));
      } else if (str.compare("+") == 0) {
        this->s3.push(new Plus(e1, e2));
      } else if (str.compare("-") == 0) {
        this->s3.push(new Minus(e1, e2));
      }
    } else {
      if (this->s3.size() < 1) {
        return nullptr;
      }
      e1 = this->s3.top();
      this->s3.pop();
      if (str.compare("^") == 0) {
        this->s3.push(new UMinus(e1));
      } else {
        this->s3.push(new UPlus(e1));
      }
    }
  }
  if (this->s3.size() != 1) {
    return nullptr;
  }
  e1 = this->s3.top();
  this->s3.pop();
  return e1;

}
/*
 * startOver - verifed that the stacks and the queue are empty and dont have strings from previous processs
 */
void Interpreter::startOver() {
  while (!this->s1.empty()) {
    this->s1.pop();
  }
  while (!this->s2.empty()) {
    this->s2.pop();
  }
  while (!this->s3.empty()) {
    this->s3.pop();
  }
}
/*
 * interpret - build an expression from a given string depending on the
 * str - the expression in a string
 * return pointer to the expression if the process succeeded
 */
Expression *Interpreter::interpret(string str) {
  startOver();
  if (!putInStack(str)) {
    throw ("bad input");
  }
  Expression *e = buildExp();
  if (e == nullptr) {
    throw ("bad input");
  }
  return e;
}




//
// Created by daniels on 07/11/2019.

#include <regex>
#include "ex1.h"
#include "Globals.h"

double Value::calculate() {
  return val;
}

Variable &Variable::operator++() {
  value++;
  return *this;
}

Variable &Variable::operator++(int) {
  value++;
  return *this;
}

Variable &Variable::operator--() {
  value--;
  return *this;
}

Variable &Variable::operator--(int) {
  value--;
  return *this;
}

Variable &Variable::operator+=(double v) {
  value += v;
  return *this;
}

Variable &Variable::operator-=(double v) {
  value -= v;
  return *this;
}

double Variable::calculate() {
  return value;
}

string Variable::getName() {
  return name;
}

double Variable::getValue() const {
  return value;
}

Variable::Variable(string n, double v) {
  // check if the variable name is valid
  if (n[0] >= '0' && n[0] <= '9')
    throw "bad input";
  for (char i : n) {
    if (!((i >= '0' && i <= '9') || i == '_' || (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z'))) {
      throw "bad input";
    }
  }
  name = n;
  value = v;
}

UnaryOperator::~UnaryOperator() {
  if (exp != nullptr)
    delete (exp);
}

double UPlus::calculate() {
  return exp->calculate();
}

double UMinus::calculate() {
  return -exp->calculate();

}

BinaryOperator::~BinaryOperator() {
  if (expL != nullptr)
    delete (expL);
  if (expR != nullptr)
    delete (expR);
}

double Plus::calculate() {
  return expL->calculate() + expR->calculate();
}

double Minus::calculate() {

  return expL->calculate() - expR->calculate();

}

double Mul::calculate() {
  return expL->calculate() * expR->calculate();

}

double Div::calculate() {
  if (expR->calculate() != 0)
    return expL->calculate() / expR->calculate();
  else throw "bad input";

}

BoolOperator::~BoolOperator() {
  if (expL != nullptr)
    delete (expL);
  if (expR != nullptr)
    delete (expR);
}

double Smaller::calculate() {
  return expL->calculate() < expR->calculate();
}
double SmallerEqual::calculate() {
  return expL->calculate() <= expR->calculate();
}
double Bigger::calculate() {
  return expL->calculate() > expR->calculate();
}
double BiggerEqual::calculate() {
  return expL->calculate() >= expR->calculate();
}
double Equal::calculate() {
  return expL->calculate() == expR->calculate();
}
double NotEqual::calculate() {
  return expL->calculate() != expR->calculate();
}

void Interpreter::setVariables(string s) {
  int j, k = 0;
  while ((unsigned) k < s.length()) {
    // scan the string, take it apart in the ';' signs, and send it to stringToVariable to save it in vMap
    j = s.substr(k, s.length()).find(';');
    stringToVariable(s.substr(k, j));
    if (j == -1) break;
    k += (j + 1);
  }
}

void Interpreter::stringToVariable(string s) {
  if (!isValidVariableString(s)) throw "bad input";
  int j, k = 0;
  string name;
  double val;
  // extract the name
  j = s.substr(k, s.length()).find('=');
  if (j == -1) throw "bad input";
  name = s.substr(k, j);
  // check the variable name validation
  if (name[0] >= '0' && name[0] <= '9') throw "bad input";
  for (char i : name) {
    if (!((i >= '0' && i <= '9') || i == '_' || (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z'))) {
      throw "bad input";
    }
  }

  // extract the value
  k += (j + 1);
  int dotCounter = 0;
  int MinusOrPlus = 0;
  j = s.substr(k, s.length()).find('=');
  //check if the string-value represent a valid double
  //check if first or last char is '.'
  if (s.substr(k, j)[0] == '.' || s.substr(k, j)[s.substr(k, j).length() - 1] == '.')
    throw "bad input";
  //check if there is any non valid character in the string, or more than 1 '.'/'+'/'-'
  for (char i : s.substr(k, j)) {
    if (((i < '0' || i > '9') && i != '.' && i != '+' && i != '-') || dotCounter > 1 || MinusOrPlus > 1) {
      throw "bad input";
    }
    if (i == '.') dotCounter++;
    if (i == '+' || i == '-') MinusOrPlus++;
  }
  //check if the minus/plus in the right place
  if (MinusOrPlus == 1) {
    if (s.substr(k, j)[0] != '+' && s.substr(k, j)[0] != '-') {
      throw "bad input";
    }
    if (s.substr(k, j)[1] == '.') throw "bad input";
  }

  const char *value = s.substr(k, j).c_str();
  val = stod(value);
  vMap[name] = val;
}

Expression *Interpreter::interpret(string stringExp) {
  // check if the parenthesis order in the right order
  stringExp = regex_replace(stringExp, regex("<="), "$");
  stringExp = regex_replace(stringExp, regex(">="), "#");
  stringExp = regex_replace(stringExp, regex("=="), "@");
  stringExp = regex_replace(stringExp, regex("!="), "!");
  if (!validParenthesis(stringExp) || stringExp.length() == 0)
    throw "bad input";

  stack<string> s;
  queue<string> q;
  int k = 0;
  while (true) {
    // get the next operator/variable/value
    string letter = getLetter(stringExp, k);
    if (letter == "end of string") break;
    // implement of the shunting yard algorithm
    if (isOperator(letter)) {
      if (s.empty() || letter == "(") { s.push(letter); }
      else if (letter == ")") {
        while (s.top() != "(") {
          q.push(s.top());
          s.pop();
        }
        s.pop();
      } else if (leftIsPrefer(letter, s.top())) {
        s.push(letter);
      } else {
        while (!leftIsPrefer(letter, s.top())) {
          q.push(s.top());
          s.pop();
          if (s.empty()) break;
        }
        s.push(letter);
      }
    } else if (isVariable(letter)) {
      q.push(letter);
    } else {
      q.push(letter);
    }
  }
  while (!s.empty()) {
    q.push(s.top());
    s.pop();
  }
  // send the postfix queue "q" to the expressionCreator
  return expressionCreator(q);
}

string Interpreter::getLetter(string s, int &k) {
  int start = k;
  if ((unsigned) k == s.length()) {
    k = -1;
    return "end of string";
  }
  // check if the string is valid, read a part of the string - operator/variable or value
  // read operator
  if (isOperator(s.substr(start, 1))) {
    if (!((s.substr(start, 1) == "(") || (s.substr(start, 1) == ")")))
      if (((s.substr(start + 1, 1) == "*") || (s.substr(start + 1, 1) == "/")))
        throw "bad input";
    if ((s.substr(start, 1) == ")") && (s.substr(start + 1, 1) == "("))
      throw "bad input";
    //Unary operators
    if (s.substr(start, 1) == "+" || s.substr(start, 1) == "-") {
      if (k == 0) {
        k++;
        if (s.substr(start, 1) == "+") { return "^"; }
        if (s.substr(start, 1) == "-") { return "%"; }
      }
      if (s.substr(start - 1, 1) == "(") {
        k++;
        if (s.substr(start, 1) == "+") { return "^"; }
        if (s.substr(start, 1) == "-") { return "%"; }
      }

    }
    if (!(s.substr(start, 1) == "+" || s.substr(start, 1) == "-") ||
        isOperator(s.substr(start + 1, 1)) ||
        s.substr(start - 1, 1) != "(") {
      if (!((s.substr(start, 1) == "+" || s.substr(start, 1) == "-") &&
          (s.substr(start + 1, 1) == "+" || s.substr(start + 1, 1) == "-" ||
              (s.substr(start + 1, 1) >= "0" && s.substr(start + 1, 1) <= "9")) &&
          isOperator(s.substr(start - 1, 1))) || s.substr(start - 1, 1) == ")") {
        k++;
        return s.substr(start, 1);
      }
    }
  }
  k++;
  // read variable or number
  for (char i : s.substr(start + 1, s.length() - 1)) {
    if (!(i == ')' || i == '(' || i == '+' || i == '-' || i == '*' || i == '/' || i == '<' || i == '$' || i == '>'
        || i == '#' || i == '@' || i == '!')) {
      if (i == 0) {
        k = -1;
        return "end of string";
      }
      k++;
    } else { break; }
  }
  return s.substr(start, k - start);
}

bool Interpreter::isOperator(string s) {
  return (s == ")" || s == "(" || s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "%"
      || s == "<" || s == "$" || s == ">" || s == "#" || s == "@" || s == "!");
}

bool Interpreter::isVariable(string s) {
  // check if the string s is a valid variable
  bool containsLetters = false;
  for (char i : s) {
    if ((i < '0' || i > '9') && i != '+' && i != '-' && i != '.') {
      containsLetters = true;
      break;
    }
  }
  if (!containsLetters) {
    return false;
  }
  // check if the variable exist in the variables map
  if (vMap.find(s) == vMap.end()) {
    throw "bad input";
  } else { return true; }
}

bool Interpreter::leftIsPrefer(string oper, string top) {
  // set of priorities for the shunting yard algorithm
  map<string, int> priorityMap;
  priorityMap["("] = 0;
  priorityMap["+"] = 2;
  priorityMap["-"] = 2;
  priorityMap["*"] = 3;
  priorityMap["/"] = 3;
  priorityMap["<"] = 1;
  priorityMap["$"] = 1;
  priorityMap[">"] = 1;
  priorityMap["#"] = 1;
  priorityMap["@"] = 1;
  priorityMap["!"] = 1;
  priorityMap["^"] = 4;
  priorityMap["%"] = 4;
  return (priorityMap[oper] > priorityMap[top]);
}

Expression *Interpreter::expressionCreator(queue<string> q) {
  // second part of the algorithm, get a queue with postfix order and create Expression out of it
  stack<Expression *> s;
  Expression *left = nullptr;
  Expression *right = nullptr;
  while (!q.empty()) {
    if (isOperator(q.front())) {
      if (q.front() == "^" || q.front() == "%") {
        if (s.empty()) throw "bad input";
        left = s.top();
        s.pop();
        if (q.front() == "^") {
          s.push(new UPlus(left));
        } else if (q.front() == "%") {
          s.push(new UMinus(left));
        } else {
          throw "bad input";
        }
        q.pop();
      } else {
        if (s.empty()) throw "bad input";
        left = s.top();
        s.pop();
        if (s.empty()) throw "bad input";
        right = s.top();
        s.pop();
        if (q.front() == "+") {
          s.push(new Plus(left, right));
        } else if (q.front() == "-") {
          s.push(new Minus(left, right));
        } else if (q.front() == "*") {
          s.push(new Mul(left, right));
        } else if (q.front() == "/") {
          s.push(new Div(left, right));
        } else if (q.front() == "<") {
          s.push(new Smaller(left, right));
        } else if (q.front() == "$") {
          s.push(new SmallerEqual(left, right));
        } else if (q.front() == ">") {
          s.push(new Bigger(left, right));
        } else if (q.front() == "#") {
          s.push(new BiggerEqual(left, right));
        } else if (q.front() == "@") {
          s.push(new Equal(left, right));
        } else if (q.front() == "!") {
          s.push(new NotEqual(left, right));
        } else {
          throw "bad input";
        }
        q.pop();
      }
    } else {
      if (isVariable(q.front())) {
        s.push(new Variable(q.front(), vMap[q.front()]));
      } else {
        s.push(new Value(stod(q.front())));
      }
      q.pop();
    }

  }
  return s.top();
}

bool Interpreter::validParenthesis(string s) {
  // check if the string has a valid parenthesis order
  queue<char> q;
  for (char i : s) {
    try {
      if (i == '(') q.push('(');
      if (i == ')') q.pop();
    } catch (...) {
      return false;
    }
  }
  return q.empty();
}

bool Interpreter::isValidVariableString(string s) {
  unsigned int counter = 0;
  for (char i : s) {
    if (i == '=') counter++;
  }
  return (counter == 1);
}


#include "Data.h"

Data::Data(string var, string simulator, int biding) {
  this->sign = biding;
  this->varName = var;
  this->sim = simulator;
}
void Data::execute(string *args) {

}
void Data::setValue(double val) {
  this->value = val;
}
double Data::getValue() {
  return this->value;
}
string Data::getSim() {
  return this->sim;
}
string Data::getVarName() {
  return this->varName;
}

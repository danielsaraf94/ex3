
#include "Data.h"

Data::Data(string str, int biding ){
  this->sign = biding;
  this->sim = str;
}

void Data::setValue(double val) {
  this->value = val;
}
double Data::getValue() {
  return this->value;
}
int Data::getSign() const {
  return sign;
}
string Data::getSim() {
  return this->sim;
}




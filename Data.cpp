//

#include "Data.h"

Data::Data(string str, int biding) {
  this->sign = biding;
  this->sim = str;
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
  return sim;
}

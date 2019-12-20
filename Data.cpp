
#include "Data.h"

Data::Data(string var, string simulator, int biding, queue<string> *queue,unordered_map<string,Data*>* map) {
  this->sign = biding;
  this->varName = var;
  this->sim = simulator;
  this->update_simulator_q = queue;
  this->symbol_table = map;
}
int Data::execute(vector<string> *string_vec, int j) {
  string str = (*string_vec)[j];
  int i = 0,l=0;
  Interpreter* interpreter = new Interpreter();
  while(i<=str.length()){
    i = getIndexAfterOp(str,l);
    l= getIndexBeforeOp(str,i);
    string varName = str.substr(i,l-i);
    if(this->symbol_table->find(varName)==this->symbol_table->end()){
      i=l+1;
      continue;
    }
    Data* data=(*this->symbol_table)[varName];
    string value = std::to_string(data->getValue());
    interpreter->setVariables(varName+"="+value);
    i=l+1;
  }
  try{
    string expression = str.substr(1);
    double newValue = interpreter->interpret(expression)->calculate();
    setValue(newValue);
  }catch (...){
    cerr<<"Something went wrong with the interpretation"<<endl;
  }
  return 2;
}
int Data::getIndexBeforeOp(string str, int i) {
  for (; i < str.length(); i++) {
    if (str[i] == '=' || str[i] == '<' || str[i] == '>' || str[i] == '/' || str[i] == '*' || str[i] == '+'
        || str[i] == '-') {
      break;
    }
  }
  return i;
}
int Data::getIndexAfterOp(string str,int i) {
  for (; i < str.length(); i++) {
    if (!(str[i] == '=' || str[i] == '<' || str[i] == '>' || str[i] == '/' || str[i] == '*' || str[i] == '+'
        || str[i] == '-')) {
      break;
    }
  }
  return i;
}
void Data::setValue(double val) {
  this->value = val;
  if(sign==1){
    this->update_simulator_q->push(this->varName);
  }
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
int Data::getSign(){
  return this->sign;
}




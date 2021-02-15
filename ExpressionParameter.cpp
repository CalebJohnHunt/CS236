#include "ExpressionParameter.h"

#include <iostream>

ExpressionParameter::ExpressionParameter(Parameter* l, char o, Parameter* r)
 : Parameter() {
    this->leftParameter = l;
    this->operation = o;
    this->rightParameter = r;
}

std::string ExpressionParameter::toString() {
    std::string s = "(";
    s += leftParameter->toString();
    s += operation;
    s += rightParameter->toString();
    s += ")";
    return s;
}
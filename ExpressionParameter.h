#pragma once

#include "Parameter.h"

class ExpressionParameter : public Parameter {
public:
    ExpressionParameter(Parameter*, char, Parameter*);
    std::string toString() override;

private:
    Parameter* leftParameter;
    char operation;
    Parameter* rightParameter;
};
#include "StringParameter.h"

StringParameter::StringParameter(std::string value)
 : Parameter() {
    this->value = value;
    this->type = ParameterType::STRING;
}

std::string StringParameter::toString() {
    return value;
}
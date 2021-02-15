#include "StringParameter.h"

StringParameter::StringParameter(std::string value)
 : Parameter() {
    this->value = value;
}

std::string StringParameter::toString() {
    return value;
}
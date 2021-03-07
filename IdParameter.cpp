#include "IdParameter.h"

IdParameter::IdParameter(std::string value)
 : Parameter() {
    this->value = value;
    this->type = ParameterType::ID;
}

std::string IdParameter::toString() {
    return value;
}
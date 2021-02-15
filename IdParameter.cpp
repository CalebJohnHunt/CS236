#include "IdParameter.h"

IdParameter::IdParameter(std::string value)
 : Parameter() {
    this->value = value;
}

std::string IdParameter::toString() {
    return value;
}
#include "Parameter.h"

#include <sstream>

Parameter::Parameter(std::string value) {
    this->value = value;
}

std::string Parameter::toString() {
    return value;
}
#include "Parameter.h"

#include <sstream>

Parameter::Parameter(std::string value) {
    // this->type = type;
    this->value = value;
}

std::string Parameter::toString() {
    // std::stringstream ss;
    // switch (type) {
    //     case (STRING):
    //         ss << "\'"
    //            << value
    //            << "\'";
    //         break;
    //     case (ID):
    //         ss << value;
    //         break;
    //     case (expression):
    //         ss << "("
    //            << value
    //            << ")";
    //         break;
    // }
    // return ss.str();
    return value;
}
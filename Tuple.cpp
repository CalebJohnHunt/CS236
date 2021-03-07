#include "Tuple.h"


bool Tuple::operator< (const Tuple & other) const {
    // compare this tuple to other tuple
    return true;
}

std::string Tuple::toString() {
    std::string s = "";
    for (std::string str : values) {
        s += str + " ";
    }
    return s;
}
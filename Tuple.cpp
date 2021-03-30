#include "Tuple.h"

Tuple::Tuple() {

}

Tuple::Tuple(std::vector<std::string>& v) {
    this->values = v;
}


bool Tuple::operator< (const Tuple & other) const {
    // compare this tuple to other tuple
    return this->values < other.values;
}

std::string Tuple::toString() const {
    std::string s = "";
    for (std::string str : values) {
        s += str + " ";
    }
    return s;
}
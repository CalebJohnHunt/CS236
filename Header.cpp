#include "Header.h"


std::string Header::toString() {
    std::string s = "";
    for (std::string str : this->attributes) {
        s += str;
        s += " ";
    }
    return s;
}
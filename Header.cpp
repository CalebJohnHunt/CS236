#include "Header.h"

Header::Header() {
    
}

Header::Header(const std::vector<std::string>& attributes) {
    this->attributes = attributes;
}

std::string Header::toString() {
    std::string s = "";
    for (std::string str : this->attributes) {
        s += str;
        s += " ";
    }
    return s;
}
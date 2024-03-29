#include "Predicate.h"

#include <sstream>

#include <iostream>

Predicate::Predicate(std::string id) {
    this->id = id;
}

Predicate::~Predicate() {
    // for (auto a: parameters) {
    //     delete a;
    // }
}

void Predicate::AddParameter(Parameter* p) {
    parameters.push_back(p);
}

std::string Predicate::toString() const {
    std::stringstream ss;
    ss << this->id
       << "(";
    for (size_t i = 0; i < parameters.size(); i++) {
        ss << parameters[i]->toString();
        if (i != parameters.size() - 1) {
            ss << ",";
        }
    }
    ss << ")";

    return ss.str();
}
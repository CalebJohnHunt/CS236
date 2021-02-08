#include "Predicate.h"

#include <sstream>

Predicate::Predicate(std::string id) {
    this->id = id;
}

void Predicate::AddParameter(Parameter* p) {
    parameters.push_back(p);
}

std::string Predicate::toString() {
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
#include "Rule.h"

Rule::Rule(Predicate head) {
    this->head = head;
}

void Rule::AddPredicate(Predicate p) {
    body.push_back(p);
}

std::string Rule::toString() {
    std::string s = head.toString();
    s += " :- ";
    for (size_t i = 0; i < body.size(); i++) {
        s += body[i].toString();
        if (i != body.size()-1) {
            s += ",";
        }
    }
    s += ".";
    
    return s;
}
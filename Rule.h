#pragma once

#include <string>
#include <vector>

#include "Predicate.h"

class Rule {
public:
    Rule(Predicate);
    std::string toString();
    void AddPredicate(Predicate);

private:
    Predicate head;
    std::vector<Predicate> body;

};
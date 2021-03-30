#pragma once

#include <string>
#include <vector>

#include "Predicate.h"

class Rule {
public:
    Rule(Predicate);
    std::string toString() const;
    void AddPredicate(Predicate);

    Predicate head;
    std::vector<Predicate> body;
private:

};
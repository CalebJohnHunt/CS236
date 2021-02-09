#pragma once

#include <vector>

#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
public:
    std::string toString();

    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
private:
};
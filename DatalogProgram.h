#pragma once

#include <vector>

#include "Predicate.h"

class DatalogProgram {
public:


private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Predicate*> rules;
};
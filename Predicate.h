#pragma once

#include <string>
#include <vector>

#include "Parameter.h"

// id(param, param, param, etc)
class Predicate {
public:
    Predicate(std::string);
    void AddParameter(Parameter*);
    std::string toString();
    std::vector<Parameter*> parameters;

private:
    std::string id;
};
#pragma once

#include <string>
#include <vector>

#include "IdParameter.h"
#include "StringParameter.h"
#include "ExpressionParameter.h"

// id(param, param, param, etc)
class Predicate {
public:
    Predicate(std::string id = "");
    ~Predicate();
    void AddParameter(Parameter*);
    std::string toString() const;
    std::vector<Parameter*> parameters;
    std::string id;

private:
};
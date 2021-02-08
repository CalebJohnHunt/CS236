#pragma once

#include <string>

class Parameter {
public:
    // enum ParameterType {STRING, ID, expression};

    Parameter(std::string);
    std::string toString();

private:
    // ParameterType type;
    std::string value;

};
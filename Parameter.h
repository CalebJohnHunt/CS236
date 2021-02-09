#pragma once

#include <string>

class Parameter {
public:

    Parameter(std::string);
    std::string toString();

private:
    std::string value;

};
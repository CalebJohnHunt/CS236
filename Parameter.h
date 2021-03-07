#pragma once

#include <string>

#include <iostream>

class Parameter {
public:

    enum ParameterType {STRING, ID};

    Parameter();
    virtual ~Parameter() {};

    virtual std::string toString() = 0;

protected:
    std::string value;
    ParameterType type;
};
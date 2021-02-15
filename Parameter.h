#pragma once

#include <string>

#include <iostream>

class Parameter {
public:

    Parameter();
    virtual ~Parameter() {};

    virtual std::string toString() = 0;

protected:
    std::string value;
};
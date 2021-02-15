#pragma once

#include "Parameter.h"

class StringParameter : public Parameter {
public:
    StringParameter(std::string);

    std::string toString() override;

private:
};
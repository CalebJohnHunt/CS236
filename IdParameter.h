#pragma once

#include "Parameter.h"

class IdParameter : public Parameter {
public:
    IdParameter(std::string value);
    std::string toString() override;

private:
};
#pragma once

#include "Automaton.h"

class IDAutomaton : public Automaton {
public:
    IDAutomaton(TokenType type=ID);
    size_t Start(const std::string& input) override;

protected:
};
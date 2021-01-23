#pragma once

#include "Automaton.h"

class StringAutomaton : public Automaton {
public:
    StringAutomaton(TokenType type = STRING);
    size_t Start(const std::string& input) override;

private:


};
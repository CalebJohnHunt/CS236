#pragma once

#include "Automaton.h"

class IDAutomaton : public Automaton {
public:
    IDAutomaton(Token::TokenType type = Token::ID);
    size_t Start(const std::string& input) override;

protected:
};
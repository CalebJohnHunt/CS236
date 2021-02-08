#pragma once

#include "Automaton.h"

class StringAutomaton : public Automaton {
public:
    StringAutomaton(Token::TokenType type = Token::STRING);
    size_t Start(const std::string& input) override;

private:


};
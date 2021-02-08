#pragma once

#include "Automaton.h"
#include <string> // Also found in Automaton.h. oh well

class MatcherAutomaton : public Automaton {
public:
    MatcherAutomaton(std::string toMatch, Token::TokenType type);
    size_t Start(const std::string& input) override;

private:
    std::string toMatch;
};
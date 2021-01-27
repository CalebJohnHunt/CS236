#pragma once

#include "Automaton.h"

class CommentAutomaton : public Automaton {
public:
    CommentAutomaton(Token::TokenType type = Token::COMMENT);
    size_t Start(const std::string& input) override;

private:
};
#pragma once

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton {
public:
    BlockCommentAutomaton(Token::TokenType type = Token::COMMENT);
    size_t Start(const std::string& input) override;


private:
};
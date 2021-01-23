#pragma once

#include "Automaton.h"

class CommentAutomaton : public Automaton {
public:
    CommentAutomaton(TokenType type = COMMENT);
    size_t Start(const std::string& input) override;

private:
};
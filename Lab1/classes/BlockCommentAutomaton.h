#pragma once

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton {
public:
    BlockCommentAutomaton(TokenType type = COMMENT);
    size_t Start(const std::string& input) override;


private:
};
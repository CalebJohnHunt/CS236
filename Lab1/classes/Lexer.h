#pragma once

#include <vector>
#include <string>

#include "Token.h"
#include "InvalidToken.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "BlockCommentAutomaton.h"


class Lexer {
public:
    Lexer();
    ~Lexer();
    void Run(std::string input);

// private:
    std::vector<Token*> tokens;
    std::vector<Automaton*> automata;

};
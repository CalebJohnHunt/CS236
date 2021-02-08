#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Token.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "BlockCommentAutomaton.h"


class Lexer {
public:
    Lexer(const std::string &fileName);
    ~Lexer();
    std::vector<Token*> Run();
    void Print();

private:
    std::vector<Token*> tokens;
    std::vector<Automaton*> automata;
    std::string input = "";

};
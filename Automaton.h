#pragma once

#include <string>

#include "Token.h"

class Automaton {
public:
    Automaton(Token::TokenType type);
    virtual ~Automaton() {};

    virtual size_t Start(const std::string& input) = 0;
    Token* CreateToken(std::string input, size_t lineNumber);
    size_t NewLinesRead() const;

protected:
    Token::TokenType type;
    size_t newLines;
    size_t inputRead = 0;

private:

};
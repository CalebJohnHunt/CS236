#pragma once

#include <string>


class Token {
public:
    const enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
                    MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING,
                    COMMENT, UNDEFINED, END}; // END == EOF
                    
    Token(TokenType type, std::string name, size_t lineNumber);
    Token(TokenType type, char charname, size_t lineNumber);

// protected:
    TokenType type;
    std::string name;
    size_t lineNumber;
};
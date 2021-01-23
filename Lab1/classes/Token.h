#pragma once

#include <string>

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
                MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING,
                COMMENT, UNDEFINED, END}; // END == EOF

class Token {
public:
    Token(TokenType type, std::string name, size_t lineNumber);

// protected:
    TokenType type;
    std::string name;
    size_t lineNumber;
};
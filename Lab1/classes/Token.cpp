#include "Token.h"

Token::Token(TokenType type, std::string name, size_t lineNumber) {
    this->type = type;
    this->name = name;
    this->lineNumber = lineNumber;
}

Token::Token(TokenType type, char charname, size_t lineNumber) {
    this->type = type;
    this->name = std::string(name);
    this->lineNumber = lineNumber;
}

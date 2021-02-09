#include "Token.h"

#include <sstream>

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

std::string Token::toString() {
    static const char *TokenTypeArr[] = {
        "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH",
        "MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING",
        "COMMENT", "UNDEFINED", "EOF"
        };
    std::stringstream ss;
    ss << "(" << TokenTypeArr[type] << ",\"" << name << "\"," << lineNumber << ")";
    return ss.str();
}
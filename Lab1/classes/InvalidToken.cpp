#include "InvalidToken.h"


InvalidToken::InvalidToken(std::string symbol, size_t lineNumber)
    : Token(UNDEFINED, symbol, lineNumber) {}

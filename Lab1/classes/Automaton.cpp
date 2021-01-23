#include "Automaton.h"

Automaton::Automaton(TokenType type) {
    this->type = type;
}

Token* Automaton::CreateToken(std::string input, size_t lineNumber) {
    return new Token(this->type, input, lineNumber);
}

size_t Automaton::NewLinesRead() const {
    return newLines;
}
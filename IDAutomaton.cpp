#include "IDAutomaton.h"

#include <iostream>

IDAutomaton::IDAutomaton(Token::TokenType type) : Automaton(type) {
    this->newLines = 0;
}

size_t IDAutomaton::Start(const std::string& input) {
    if (isalpha(input[0])) {
        this->inputRead = 0;
        while (isalnum(input[++inputRead])) {
            if (this->inputRead > 100) {std::cout << "INFINITE LOOP!\n"; return 0;}
        }
        return inputRead;
    }
    return 0;
}
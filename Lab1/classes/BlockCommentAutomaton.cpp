#include "BlockCommentAutomaton.h"

#include <iostream>

BlockCommentAutomaton::BlockCommentAutomaton(Token::TokenType type)
    : Automaton(type) {
    this->newLines = 0;
}

size_t BlockCommentAutomaton::Start(const std::string& input) {
    this->inputRead = 0;
    this->newLines = 0;
    if (input[0] == '#' && input[1] == '|') {
        this->type = Token::COMMENT;
        this->inputRead = 2;
        while (input[inputRead]) {
            if (input[inputRead] == '|' && input[inputRead+1] == '#') {
                inputRead += 2;
                return inputRead;
            }

            if (input[inputRead] == '\n') {
                newLines++;
            }

            inputRead++;
        }
        // Got to EOF before finding end of comment
        this->type = Token::UNDEFINED;
    }
    return inputRead;
}
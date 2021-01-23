#include "CommentAutomaton.h"

CommentAutomaton::CommentAutomaton(TokenType type)
    : Automaton(type) {
    this->newLines = 0;
}

size_t CommentAutomaton::Start(const std::string& input) {
    this->inputRead = 0;
    if (input[0] == '#') {
        while (input[inputRead] != '\n' && input[inputRead]) {
            inputRead++;
        }
        return inputRead;
    }
    return 0;
}
#include "CommentAutomaton.h"

CommentAutomaton::CommentAutomaton(TokenType type)
    : Automaton(type) {
    this->newLines = 0;
}

size_t CommentAutomaton::Start(const std::string& input) {
    this->inputRead = 0;
    // Line starts with #, but is NOT #| (denoting a block comment)
    if (input[0] == '#' && input[1] != '|') {
        while (input[inputRead] != '\n' && input[inputRead]) {
            inputRead++;
        }
        return inputRead;
    }
    return 0;
}
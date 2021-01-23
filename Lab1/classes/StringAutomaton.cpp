#include "StringAutomaton.h"

StringAutomaton::StringAutomaton(TokenType type)
    : Automaton(type) {
}

size_t StringAutomaton::Start(const std::string& input) {
    if (input[0] == '\'') {
        this->newLines = 0;
        this->type = STRING;
        inputRead = 1;
        while (inputRead < input.size()) {
            if (input[inputRead] == '\'') {
                if (input[inputRead+1] == '\'') {
                    inputRead += 2;
                    continue;
                }
                else {
                    return ++inputRead;
                }
            }
            
            if (input[inputRead] == '\n') {
                this->newLines++;
            }

            inputRead++;
        }
        // we got to the end of the file :(
        this->type = UNDEFINED;
        return inputRead;
    }
    return 0;
}
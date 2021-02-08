#include "MatcherAutomaton.h"

MatcherAutomaton::MatcherAutomaton(std::string toMatch, Token::TokenType type)
    : Automaton(type) {
    this->toMatch = toMatch;
    this->newLines = 0;
}

size_t MatcherAutomaton::Start(const std::string& input) {
    bool isMatch = true;
    this->inputRead = 0;
    for (size_t i = 0; i < toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
    }
    if (isMatch) {
        inputRead = toMatch.size();
    }
    return inputRead;
    
    // I'm pretty sure the following code is the same as the above, but compressed
    /*
    for (size_t i = 0; i < toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            return 0;
        }
    }
    return toMatch.size();
    */
}
#include "Lexer.h"

#include <iostream>
#include <string>

Lexer::Lexer() {
    tokens = std::vector<Token*>();
    automata = std::vector<Automaton*>();
    // Matching automata first
    automata.push_back(new MatcherAutomaton(",",  COMMA));
    automata.push_back(new MatcherAutomaton(".",  PERIOD));
    automata.push_back(new MatcherAutomaton("?",  Q_MARK));
    automata.push_back(new MatcherAutomaton("(",  LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")",  RIGHT_PAREN));
    automata.push_back(new MatcherAutomaton(":",  COLON));
    automata.push_back(new MatcherAutomaton(":-", COLON_DASH));
    automata.push_back(new MatcherAutomaton("*",  MULTIPLY));
    automata.push_back(new MatcherAutomaton("+",  ADD));
    automata.push_back(new MatcherAutomaton("\0",  END));
    automata.push_back(new MatcherAutomaton("Schemes", SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts",   FACTS));
    automata.push_back(new MatcherAutomaton("Rules",   RULES));
    automata.push_back(new MatcherAutomaton("Queries", QUERIES));
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new BlockCommentAutomaton());

    // ID, STRING, COMMENT, EOF?
    /*
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    */
}

void Lexer::Run(std::string input) {
    // std::cout << "RUN INPUT: " << input << std::endl;
    size_t lineNumber = 1;
    while (input.size() > 0) {
        // std::cout << "WHILE INPUT: " << input << std::endl;
        size_t maxRead = 0;
        Automaton *maxAutomaton = automata[0];
        if (isspace(input[0])) {
            if (input[0] == '\n') {
                lineNumber++;
            }
            input.erase(0,1);
            continue;
        }

        for (Automaton *curAuto : automata) {
            size_t inputRead = curAuto->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = curAuto;
            }
        }

        if (maxRead > 0) {
            Token *newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else {
            maxRead = 1;
            Token *newToken = new InvalidToken(std::string(1, input[0]), lineNumber);
            tokens.push_back(newToken);
        }
        // input = input.substr(maxRead, input.size());
        input.erase(0, maxRead);
    }

    // Add EOF token
    tokens.push_back(new Token(END, "", lineNumber));
}
#include "Lexer.h"

#include <iostream>
#include <string>

Lexer::Lexer(const std::string &file_name) {
    // Read file
    std::fstream f(file_name);
    if (f) {
        std::stringstream ss;
        ss << f.rdbuf();
        this->input = ss.str();
    }
    else {
        throw "Bad input file";
    }

    tokens = std::vector<Token*>();
    automata = std::vector<Automaton*>();

    // Matching automata first
    automata.push_back(new MatcherAutomaton(",",  Token::COMMA));
    automata.push_back(new MatcherAutomaton(".",  Token::PERIOD));
    automata.push_back(new MatcherAutomaton("?",  Token::Q_MARK));
    automata.push_back(new MatcherAutomaton("(",  Token::LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")",  Token::RIGHT_PAREN));
    automata.push_back(new MatcherAutomaton(":",  Token::COLON));
    automata.push_back(new MatcherAutomaton(":-", Token::COLON_DASH));
    automata.push_back(new MatcherAutomaton("*",  Token::MULTIPLY));
    automata.push_back(new MatcherAutomaton("+",  Token::ADD));
    automata.push_back(new MatcherAutomaton("Schemes", Token::SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts",   Token::FACTS));
    automata.push_back(new MatcherAutomaton("Rules",   Token::RULES));
    automata.push_back(new MatcherAutomaton("Queries", Token::QUERIES));
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new CommentAutomaton());
}

Lexer::~Lexer() {
    for (Token* a : tokens) {
        delete a;
    }
    for (Automaton* a : automata) {
        delete a;
    }
}

void Lexer::Run() {
    size_t lineNumber = 1;
    while (input.size() > 0) {
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
            tokens.push_back(new Token(Token::UNDEFINED, std::string(1, input[0]), lineNumber));
        }
        input.erase(0, maxRead);
    }

    // Add EOF token
    tokens.push_back(new Token(Token::END, "", lineNumber));
}

void Lexer::Print() {
    // Convert enum TokenType to appropriate string (see Token.h)
    const char *TokenTypeArr[] = {
        "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH",
        "MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING",
        "COMMENT", "UNDEFINED", "EOF"
        };
    
    for (Token* T : tokens) {
        std::cout << '(' << TokenTypeArr[T->type] << ",\"" << T->name << "\"," << T->lineNumber << ')' << std::endl;
    }

    std::cout << "Total Tokens = " << tokens.size();
}
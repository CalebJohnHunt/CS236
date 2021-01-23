#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <string.h>

#include "./classes/Lexer.h"


int main(int argc, char **argv) {
    std::stringstream ss;

    // Check command line for file
    if (argc > 1) {
        // Read file
        std::ifstream File(argv[1]);
        if (File) {
            ss << File.rdbuf();
        }
    }

    // Convert enum TokenType to appropriate string (see Token.h)
    std::string TokenTypeArr[] = {"COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH",
                "MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING",
                "COMMENT", "UNDEFINED", "EOF"};

    Lexer l = Lexer();
    l.Run(ss.str());

    // stdout each token
    // (TOKENTYPE,"name",lineNumber)
    for (Token* T : l.tokens) {
        std::cout << '(' << TokenTypeArr[T->type] << ",\"" << T->name << "\"," << T->lineNumber << ')' << std::endl;
    }

    std::cout << "Total Tokens = " << l.tokens.size();

    return 0;
}
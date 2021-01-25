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

    // Run lexer
    Lexer *l = new Lexer();
    l->Run(ss.str());

    // Print tokens
    l->Print();
    
    // Clean up
    delete l;

    return 0;
}
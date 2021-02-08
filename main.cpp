#include <iostream>
#include <string>

#include "./classes/Lexer.h"


int main(int argc, char **argv) {
    // Check command line for file
    if (argc > 1) {
        Lexer *l = new Lexer(argv[1]);
        
        // Run lexer
        l->Run();

        // Print tokens
        l->Print();
        
        // Clean up
        delete l;
        
    }
    else {
        std::cout << "No parameter given\n";
        return 1;
    }


    return 0;
}
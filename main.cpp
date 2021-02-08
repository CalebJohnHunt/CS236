#include <iostream>
#include <string>

#include "Lexer.h"
#include "Parser.h"

int main(int argc, char **argv) {
    // Check command line for file
    if (argc > 1) {
        Lexer *l = new Lexer(argv[1]);
        
        // Run lexer
        std::vector<Token*> tokens = l->Run();

        // Print tokens
        l->Print();
        

        Parser* p = new Parser(tokens);
        p->Parse();





        
        // Clean up
        delete l;
        delete p;
    }
    else {
        std::cout << "No parameter given\n";
        return 1;
    }


    return 0;
}
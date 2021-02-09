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

        // Print tokens Lab1
        // l->Print();
        

        Parser* p = new Parser(tokens);
        DatalogProgram* d = p->Parse();
        
        // Print DatalogProgram Lab2
        if (d != NULL) {
            std::cout << "Success!\n"
                      << d->toString();
        }



        
        // Clean up
        delete l;
        delete p;
        delete d;
    }
    else {
        std::cout << "No parameter given\n";
        return 1;
    }


    return 0;
}
#include <iostream>
#include <string>

#include "Lexer.h"       // lab 1
#include "Parser.h"      // lab 2
#include "Interpreter.h" // lab 3

int main(int argc, char **argv) {

    // Compressed Lab 2 pass off
    // DatalogProgram* d = Parser(Lexer(argv[1]).Run()).Parse();
    // if (d != NULL) {
    //     std::cout << "Success!\n"
    //               << d->toString();
    // }

    // Check command line for file
    if (argc > 1) {
        Lexer *l;
        try {
            l = new Lexer(argv[1]);
        }
        catch (const char* e) {
            std::cout << e << ". Ending early.\n";
            return 0;
        }

        // Run lexer
        std::vector<Token*> tokens = l->Run();

        // Print tokens Lab1
        // l->Print();
        

        Parser* p = new Parser(tokens);
        DatalogProgram* d = p->Parse();
        
        // Print DatalogProgram Lab2
        // if (d != NULL) {
        //     std::cout << "Success!\n"
        //               << d->toString();
        // }

        Interpreter* i = new Interpreter(d);
        i->Interpret();

        std::cout << "**********\nDatabase:\n" << i->dataBase->toString() << "\n";



        
        // Clean up
        delete l;
        delete p;
        delete d;
        delete i;
    }
    else {
        std::cout << "No parameter given\n";
        return 0;
    }


    return 0;
}
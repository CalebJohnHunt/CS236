#pragma once

#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
public:
    Interpreter(DatalogProgram*);
    void Interpret();
    Relation* evaluatePredicate(const Predicate &p);

    DatalogProgram* dataProg;
    Database* dataBase;
private:

    // Helper functions to keep code clear
    Tuple* evaluateTuplePredicate(const Predicate &p);
    void selectConstants(Relation&, Predicate&);
    void selectVariables(Relation&, Predicate&);

};
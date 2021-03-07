#pragma once

#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
public:
    Interpreter(DatalogProgram*);
    void Interpret();
    Relation* evaluatePredicate(const Predicate &p);
    Tuple* evaluateTuplePredicate(const Predicate &p);

    DatalogProgram* dataProg;
    Database* dataBase;
private:

};
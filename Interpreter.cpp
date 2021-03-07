#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram* d) {
    this->dataProg = d;
    this->dataBase = new Database();
}

void Interpreter::Interpret() {
    // Evaluate schemes
    // Each scheme is a predicate. Turn them into relations, and add them to the database
    for (Predicate s : dataProg->schemes) {
        dataBase->addRelation(evaluatePredicate(s));
    }

    // Evaluate facts
    // Each fact is a predicate, but we only care about its parameters, so don't turn it into a relation
    // Turn each one into a Tuple of its parameters. Then add the tuple to the relation (found in nameRelationMap)
    for (Predicate f : dataProg->facts) {
        Tuple* t = evaluateTuplePredicate(f);
        dataBase->nameRelationMap[f.id]->tuples.insert(t);
    }

    // Evaluate queries
    for (Predicate q : dataProg->queries) {
        Relation r = *dataBase->nameRelationMap[q.id]; // get relation with same name as query
        // select for each constant in query
        // for (size_t i = 0; i < q.parameters.size(); i++) {
        //     if (q.parameters[i].)
        //     Relation r_constant_selected = r.select()
        // }
        // select for each pair of matching variable in query
        // project using the positions of the variables in query
        // rename to match the names of variables in query
        // rpint the resulting relation
    }
}

Relation* Interpreter::evaluatePredicate(const Predicate &p) {
    Relation* r = new Relation(p.id); // New relation with predicate id as its name
    for (Parameter* param : p.parameters) {
        r->addColumn(param->toString()); // param->toString() just returns its name anyway, but its name is private
    }
    return r;
}

Tuple* Interpreter::evaluateTuplePredicate(const Predicate &p) {
    Tuple* t = new Tuple();
    for (Parameter* param : p.parameters) {
        t->values.push_back(param->toString());
    }
    return t;
}
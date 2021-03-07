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
        selectConstants(r, q);
        // select for each pair of matching variable in query
        selectVariables(r, q);
        // project using the positions of the variables in query
        projectVariables(r, q);
        // rename to match the names of variables in query
        renameVariables(r, q);
        // print the resulting relation
        
        std::cout << "Query complete:\n" << q.toString() << '\n' << r.toString() << std::endl;
    }
}

Relation* Interpreter::evaluatePredicate(const Predicate &p) {
    Relation* r = new Relation(p.id); // New relation with predicate id as its name
    for (Parameter* param : p.parameters) {
        r->addColumn(param->toString()); // param->toString() just returns its name anyway, but its name is private
    }
    return r;
}

/***************************************
 * Helper functions to keep code clear *
 ***************************************/

Tuple* Interpreter::evaluateTuplePredicate(const Predicate &p) {
    Tuple* t = new Tuple();
    for (Parameter* param : p.parameters) {
        t->values.push_back(param->toString());
    }
    return t;
}

// select for each constant in the query
void Interpreter::selectConstants(Relation& r, Predicate& q) {
    for (size_t i = 0; i < q.parameters.size(); i++) {
        if (q.parameters[i]->type == Parameter::ParameterType::STRING) { // Select if parameter is constant (not variable)
            r = r.select(i, q.parameters[i]->toString());
        }
    }
}

// select for each pair of matching variables in query
void Interpreter::selectVariables(Relation& r, Predicate& q) {
    // index through each parameter except the last one (cause it'll never have a matching variable)
    for (size_t i = 0; i < q.parameters.size()-1; i++) {
        // if this parameter is a variable
        if (q.parameters[i]->type == Parameter::ParameterType::ID) {
            // index through the remaining parameters (after the ith)
            for (size_t j = i+1; j < q.parameters.size(); j++) {
                // if this second parameter is a variable
                if (q.parameters[j]->type == Parameter::ParameterType::ID) {
                    // if the variables are the same
                    if (q.parameters[i]->toString() == q.parameters[j]->toString()) {
                        r = r.select(i, j);
                    }
                }
            }
        }
    }
}

void Interpreter::projectVariables(Relation& r, Predicate& q) {
    std::vector<size_t> indices;
    // Populate indices
    for (size_t i = 0; i < q.parameters.size(); i++) {
        // if this parameter is a variable
        if (q.parameters[i]->type == Parameter::ParameterType::ID) {
            // add it to the index list
            indices.push_back(i);
        }
    }

    // Project
    r = r.project(indices);
}

void Interpreter::renameVariables(Relation& r, Predicate& q) {
    std::vector<std::string> names;
    for (Parameter* p : q.parameters) {
        if (p->type == Parameter::ParameterType::ID) {
            names.push_back(p->toString());
        }
    }
    r = r.rename(names);
}
#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram* d) {
    this->dataProg = d;
    this->dataBase = new Database();
}

void Interpreter::Interpret() {
    // Evaluate schemes
    // Each scheme is a predicate. Turn them into relations, and add them to the database
    for (const Predicate& s : dataProg->schemes) {
        dataBase->addRelation(evaluatePredicate(s));
    }

    // Evaluate facts
    // Each fact is a predicate, but we only care about its parameters, so don't turn it into a relation
    // Turn each one into a Tuple of its parameters. Then add the tuple to the relation (found in nameRelationMap)
    for (const Predicate& f : dataProg->facts) {
        Tuple t = evaluateTuplePredicate(f);
        dataBase->nameRelationMap[f.id]->tuples.insert(t);
    }

    // Evalutate rules
    for (const Rule& rule : dataProg->rules) {
        // Evaluate queries

        // Get the first predicate done, then we'll try to join it to the others
        Predicate p = rule.body[0];
        Relation r = *dataBase->nameRelationMap[p.id];
        selectConstants(r, p);
        selectVariables(r, p);
        projectVariables(r, p);
        renameVariables(r, p);
        for (size_t i = 1; i < rule.body.size(); i++) {
            // std::cout << "Join " << i << ":" << std::endl << r.toString();
            p = rule.body[i];
            Relation r_temp = *dataBase->nameRelationMap[p.id];
            // std::cout << "Relation before selects/project/rename: \n" << r_temp.toString() << std::endl;
            selectConstants(r_temp, p);
            selectVariables(r_temp, p);
            projectVariables(r_temp, p);
            renameVariables(r_temp, p);
            r = r.join(r_temp);
        }
        // std::cout << "After joining: \n" << r.toString() << std::endl;
        std::vector<size_t> projectionIndices;
        // For each ID of the lefthand side
        for (Parameter* p : rule.head.parameters) {
            const std::string s = p->toString();
            // Look through the headers of our joined relation
            for (size_t i = 0; i < r.header.attributes.size(); i++) {
                // When they match, add the index so we can project it later
                if (s == r.header.attributes[i]) {
                    projectionIndices.push_back(i);
                    break;
                }
            }
        }
        r = r.project(projectionIndices);
        std::cout << "Final relation:\n" << r.toString() << std::endl;
    }

    // Evaluate queries
    for (const Predicate& q : dataProg->queries) {
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
        printQuery(r, q);
        // std::cout << "Query complete:\n" << q.toString() << '\n' << r.toString() << std::endl;
    }
}

Relation* Interpreter::evaluatePredicate(const Predicate &p) {
    Relation* r = new Relation(p.id); // New relation with predicate id as its name
    for (Parameter* param : p.parameters) {
        // Only add the ID's. This is always true for schemes, but not always for rules
        if (param->type == Parameter::ID)
            r->addColumn(param->toString()); // param->toString() just returns its name anyway, but its name is private
    }
    return r;
}

/***************************************
 * Helper functions to keep code clear *
 ***************************************/

Tuple Interpreter::evaluateTuplePredicate(const Predicate &p) {
    Tuple t = Tuple();
    for (Parameter* param : p.parameters) {
        t.values.push_back(param->toString());
    }
    return t;
}

// select for each constant in the query
void Interpreter::selectConstants(Relation& r, const Predicate& q) {
    for (size_t i = 0; i < q.parameters.size(); i++) {
        if (q.parameters[i]->type == Parameter::ParameterType::STRING) { // Select if parameter is constant (not variable)
            r = r.select(i, q.parameters[i]->toString());
        }
    }
}

// select for each pair of matching variables in query
void Interpreter::selectVariables(Relation& r, const Predicate& q) {
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

void Interpreter::projectVariables(Relation& r, const Predicate& q) {
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

void Interpreter::renameVariables(Relation& r, const Predicate& q) {
    std::vector<std::string> names;
    for (Parameter* p : q.parameters) {
        if (p->type == Parameter::ParameterType::ID) {
            names.push_back(p->toString());
        }
    }
    r = r.rename(names);
}

void Interpreter::printQuery(Relation& r, const Predicate& q) {
    std::cout << "Query Evaluation" << std::endl; // Only needed for proj 4
    std::cout << q.toString() << "? "; // SNAP('caleb', 1234, A, P)?
    if (r.tuples.size() > 0) {
        std::cout << "Yes(" << r.tuples.size() << ")\n"; // Yes(#)
    } else {
        std::cout << "No\n"; // No
    }


    for (Tuple t : r.tuples) {
        if (t.values.size() == 0)
            continue;
        std::set<std::string> printedAttributes;
        std::cout << "  ";
        for (size_t i = 0; i < t.values.size(); i++) {
            std::string attr = r.header.attributes[i];
            if (printedAttributes.find(attr) == printedAttributes.end()) { // This is a new attribute
                printedAttributes.insert(attr);
                if (printedAttributes.size() > 1) { // This isn't the first attribute
                    std::cout << ", ";
                }
                std::cout << attr << "=" << t.values[i];
            }
        }
        // As long as we got an attribute to show
        if (printedAttributes.size() != 0)
            std::cout << '\n';
    }

}
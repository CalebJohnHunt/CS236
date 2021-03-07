#include "Relation.h"

// Constructor. Takes a name, init our header
Relation::Relation(std::string name) {
    this->name = name;
    this->header = Header();
}

// Constructor. Copies old relation's name and headers
Relation::Relation(Relation* r) {
    this->name = r->name;
    this->header = r->header;
}

// Add a column called attribute to our header
void Relation::addColumn(std::string attribute) {
    this->header.attributes.push_back(attribute);
}

Relation Relation::select(size_t index, std::string value) {
    Relation r = Relation(this); // Make a new relation based on the current one (copies name and header)
    for (Tuple* t : this->tuples) {
        if (t->values[index] == value) {
            r.tuples.insert(t);
        }
    }
    return r;
}

Relation Relation::select(size_t index, size_t index2) {
    Relation r = Relation(this); // Make a new relation based on the current one (copies name and header)
    for (Tuple* t : this->tuples) {
        if (t->values[index] == t->values[index2]) { // if those two spots are matching in the tuple
            r.tuples.insert(t);
        }
    }
    return r;
}


std::string Relation::toString() {
    std::string s = "";
    s += this->name + ":\n";
    s += this->header.toString() + "\n";
    for (Tuple* t : tuples) {
        s += t->toString() + "\n";
    }
    return s;
}
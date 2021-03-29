#include "Relation.h"

#include <iostream>

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

Relation Relation::select(size_t& index, std::string value) {
    Relation r = Relation(this); // Make a new relation based on the current one (copies name and header)
    for (Tuple t : this->tuples) {
        if (t.values[index] == value) {
            r.tuples.insert(t);
        }
    }
    return r;
}

Relation Relation::select(size_t& index, size_t& index2) {
    Relation r = Relation(this); // Make a new relation based on the current one (copies name and header)
    for (Tuple t : this->tuples) {
        if (t.values[index] == t.values[index2]) { // if those two spots are matching in the tuple
            r.tuples.insert(t);
        }
    }
    return r;
}

Relation Relation::project(std::vector<size_t>& indices) {
    Relation r = Relation(this->name);
    for (size_t i : indices) {
        r.addColumn(this->header.attributes[i]); // Add attributes to new Relation
    }
    for (Tuple t : this->tuples) {
        std::vector<std::string> v;
        for (size_t i : indices) {
            v.push_back(t.values[i]); // Store correct attribute values of tuple
        }
        r.tuples.insert(Tuple(v)); // Add projected tuple to new relation
    }
    return r;
}

Relation Relation::rename(std::vector<std::string>& names) {
    Relation r = Relation(this->name);
    r.header = Header(names);
    r.tuples = this->tuples;
    return r;
}

Relation Relation::rUnion(Relation& o) {
    Relation r = Relation(*this); // Make total copy, not just the name and header like in Relation(Relation*)
    // std::cout << "Union called. Old relation:\n" << r.toString() << "\nNew Tuples added:\n";
    for (Tuple t : o.tuples) {
        r.tuples.insert(t);
        // Print out the tuple if successful (testing)
        // if (this->tuples.insert(t).second) {
        //     std::cout << t.toString() << std::endl;
        // }
    }
    return r;
}

Relation Relation::join(Relation& o) {
    Relation r = Relation(*this);
}

std::string Relation::toString() {
    std::string s = "";
    s += this->name + ":\n";
    s += this->header.toString() + "\n";
    for (Tuple t : tuples) {
        s += t.toString() + "\n";
    }
    return s;
}
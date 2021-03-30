#include "Relation.h"

#include <iostream>
#include <algorithm> // std::find used in combineHeaders

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

Relation Relation::select(const size_t& index, const std::string value) {
    Relation r = Relation(this); // Make a new relation based on the current one (copies name and header)
    for (Tuple t : this->tuples) {
        if (t.values[index] == value) {
            r.tuples.insert(t);
        }
    }
    return r;
}

Relation Relation::select(const size_t& index, const size_t& index2) {
    Relation r = Relation(this); // Make a new relation based on the current one (copies name and header)
    for (Tuple t : this->tuples) {
        if (t.values[index] == t.values[index2]) { // if those two spots are matching in the tuple
            r.tuples.insert(t);
        }
    }
    return r;
}

Relation Relation::project(const std::vector<size_t>& indices) {
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

Relation Relation::rename(const std::vector<std::string>& names) {
    Relation r = Relation(this->name);
    r.header = Header(names);
    r.tuples = this->tuples;
    return r;
}

Relation Relation::rUnion(const Relation& o) {
    Relation r = Relation(*this); // Make total copy, not just the name and header like in Relation(Relation*)
    // std::cout << "Union called. Old relation:\n" << r.toString() << "\nNew Tuples added:\n";
    for (const Tuple& t : o.tuples) {
        r.tuples.insert(t);
        // Print out the tuple if successful (testing)
        // if (this->tuples.insert(t).second) {
        //     std::cout << t.toString() << std::endl;
        // }
    }
    return r;
}

Relation Relation::join(const Relation& o) {
    Relation r = Relation(*this);

    std::cout << "\njoin testing\n" << std::endl;

    // combine the headers (this headers go before other headers)
    std::cout << "combineHeaders test" << std::endl;
    Header h = combineHeaders(r.header, o.header);
    r.header = h;
    std::cout << h.toString() << std::endl;

    // combine tuples
    // Go through every pair of tuples
    for (const Tuple& rt : r.tuples) {
        for (const Tuple& ot : o.tuples) {
            if (isJoinable(rt, ot)) {
                Tuple ct = combineTuples(rt, ot);
                r.tuples.insert(ct);
            }
        }
    }

    return r;

}

Header Relation::combineHeaders(const Header& h, const Header& o) {
    std::vector<std::string> combinedAttributes;
    for (std::string attribute : h.attributes) {
        // if this header attribute is not in the combinedAttributes, add it
        if (find(combinedAttributes.begin(), combinedAttributes.end(), attribute) == combinedAttributes.end()) {
            combinedAttributes.push_back(attribute);
        }
    }
    for (const std::string attribute : o.attributes) {
        // if this header attribute is not in the combinedAttributes, add it
        if (find(combinedAttributes.begin(), combinedAttributes.end(), attribute) == combinedAttributes.end()) {
            combinedAttributes.push_back(attribute);
        }
    }

    return Header(combinedAttributes);
}

bool Relation::isJoinable(const Tuple& t, const Tuple& o) {
    return true;
}

Tuple Relation::combineTuples(const Tuple& t, const Tuple& o) {
    return t;
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
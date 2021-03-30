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

void Relation::rUnion(const Relation& o) {
    //Relation r = Relation(*this); // Make total copy, not just the name and header like in Relation(Relation*)
    // std::cout << "Union called. Old relation:\n" << r.toString() << "\nNew Tuples added:\n";
    for (const Tuple& t : o.tuples) {
        this->tuples.insert(t);
        // Print out the tuple if successful (testing)
        // if (this->tuples.insert(t).second) {
        //     std::cout << t.toString() << std::endl;
        // }
    }
    // return r;
}

Relation Relation::join(const Relation& o) {
    Relation r = Relation(this);

    // std::cout << "\njoining\n" << this->toString() << std::endl << o.toString() << std::endl;

    // combine the headers (this headers go before other headers)
    Header h = combineHeaders(this->header, o.header);
    r.header = h;

    // Find all shared attributes
    std::vector<std::pair<size_t, size_t>> sharedAttributesIndices;
    for (size_t i = 0; i < this->header.attributes.size(); i++) {
        for (size_t j = 0; j < o.header.attributes.size(); j++) {
            // We've found a matching attribute. Store the indices for joining later
            if (this->header.attributes[i] == o.header.attributes[j]) {
                sharedAttributesIndices.push_back(std::pair<size_t, size_t>(i, j));
                continue;
            }
        }
    }

    // combine tuples
    // Go through every pair of tuples
    for (const Tuple& rt : this->tuples) {
        for (const Tuple& ot : o.tuples) {
            Tuple ct;
            if (isJoinable(rt, ot, sharedAttributesIndices)) {
                ct = combineTuples(rt, ot, sharedAttributesIndices);
                r.tuples.insert(ct);
            } else {
                // Give it an empty sharedAttributesIndices, and it will just union them
                // ct = combineTuples(rt, ct, std::vector<std::pair<size_t, size_t>>());
                continue;
            }
            // std::cout << "Tried to combine: " << rt.toString() << " | " << ot.toString() << std::endl;
            // std::cout << "Ended up: " << ct.toString() << std::endl;
        }
    }
    return r;
}

// Set subtraction. Loop through every tuple in r,
// and try to subtract it from this
void Relation::subtract(const Relation& r) {
    for (Tuple t : r.tuples) {
        this->tuples.erase(t);
    }
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

bool Relation::isJoinable(const Tuple& t, const Tuple& o, const std::vector<std::pair<size_t, size_t>>& sharedAttributesIndices) {
    /*
     * Check if for each sharedAttribute, the two Tuples have the same value
     * ex: checking [0]: [2,4,5] + [3,4,5] => false
     */
    // std::cout << "isJoinable?\n" << t.toString() << "+ " << o.toString() << std::endl;
    for (const std::pair<size_t, size_t>& p : sharedAttributesIndices) {
        if (t.values[p.first] != o.values[p.second]) {
            // std::cout << "Not joinable" << std::endl;
            return false;
        }
    }
    // std::cout << "Joinable!" << std::endl;
    return true;
}

Tuple Relation::combineTuples(const Tuple& t, const Tuple& o, const std::vector<std::pair<size_t, size_t>>& sharedAttributesIndices) {
    /*
     * Takes in two tuples. Returns the second appeneded to the first
     * but with shared attributes only appearing once (as part of the first tuple)
     * e.g. [1,2,3,4] + [a,4,b,c] -> [1,2,3,4,a,b,c]
     */
    
    Tuple newTuple;
    // All of the values from the first tuple go in in order
    for (const std::string& s : t.values) {
        newTuple.values.push_back(s);
    }
    // Then we add on the values from the other tuple (unless they're the shared ones)
    for (size_t i = 0; i < o.values.size(); i++) {
        // Make sure to not append the shared attributes again
        bool uniqueAttribute = true;
        for (const std::pair<size_t, size_t>& p : sharedAttributesIndices) {
            // This index is one of the shared ones. Skip it.
            if (i == p.second) {
                uniqueAttribute = false;
                break;
            }
        }
        if (!uniqueAttribute) {
            continue;
        }

        newTuple.values.push_back(o.values[i]);
    }
    return newTuple;
}


std::string Relation::toString() const {
    std::string s = "";
    s += this->name + ":\n";
    s += this->header.toString() + "\n";
    for (Tuple t : tuples) {
        s += t.toString() + "\n";
    }
    return s;
}
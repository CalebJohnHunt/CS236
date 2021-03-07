#pragma once

#include <set>
#include <vector>

#include "Header.h"
#include "Tuple.h"

class Relation {
public:
    Relation(std::string name);
    Relation(Relation* r);

    void addColumn(std::string attribute);

    Relation select(size_t& index, std::string value); // index and value (relation column and value to select)
    Relation select(size_t& index, size_t& index2);     // index and index (relation columns to select on same values)
    Relation project(std::vector<size_t>& indices);     // list of indices (the columns to keep)
    Relation rename(std::vector<size_t>& indices);      // list of attributes (defines the new header)

    Header header;    // S, N, A, P
    std::string name; // SNAP
    std::set<Tuple*> tuples;

    std::string toString();

private:

};
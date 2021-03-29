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
    Relation select(size_t& index, size_t& index2);    // index and index (relation columns to select on same values)
    Relation project(std::vector<size_t>& indices);    // list of indices (the columns to keep)
    Relation rename(std::vector<std::string>& names);  // list of attributes (defines the new header)
    Relation rUnion(Relation& r);                      // Relation $\cup$ r
    Relation join(Relation& r);                        // Relation |x| r

    Header header;    // S, N, A, P
    std::string name; // SNAP
    std::set<Tuple> tuples;

    std::string toString();

private:
    // join helper functions
    Header combineHeaders(Header& h, Header& o);
    bool isJoinable(Tuple& t, Tuple& o);
    Tuple combineTuples(Tuple& t, Tuple& o);
};
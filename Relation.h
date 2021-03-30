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

    Relation select(const size_t& index, const std::string value); // index and value (relation column and value to select)
    Relation select(const size_t& index, const size_t& index2);    // index and index (relation columns to select on same values)
    Relation project(const std::vector<size_t>& indices);          // list of indices (the columns to keep)
    Relation rename(const std::vector<std::string>& names);        // list of attributes (defines the new header)
    Relation rUnion(const Relation& r);                            // Relation $\cup$ r
    Relation join(const Relation& r);                              // Relation |x| r

    Header header;    // S, N, A, P
    std::string name; // SNAP
    std::set<Tuple> tuples;

    std::string toString() const;

private:
    // join helper functions
    Header combineHeaders(const Header& h, const Header& o);
    bool isJoinable(const Tuple& t, const Tuple& o, const std::vector<std::pair<size_t, size_t>>& sharedAttributesIndices);
    Tuple combineTuples(const Tuple& t, const Tuple& o, const std::vector<std::pair<size_t, size_t>>& sharedAttributesIndices);
};
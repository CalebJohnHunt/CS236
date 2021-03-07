#pragma once

#include <vector>
#include <map>
#include <string>

#include "Relation.h"
#include "Header.h"

class Database {
public:
    void addRelation(Relation*);
    std::map<std::string, Relation*> nameRelationMap;

    std::string toString();

private:
};
#include "Database.h"

#include <iostream>

void Database::addRelation(Relation* r) {
    this->nameRelationMap[r->name] = r;
}

std::string Database::toString() {
    std::string s = "";
    std::map<std::string, Relation*>::iterator it;
    for (it = this->nameRelationMap.begin(); it != this->nameRelationMap.end(); it++) {
        s += it->second->toString(); // As part of relation::toString(), it will say its name, so no need for it->first
        s += "\n";
    }
    return s;
}
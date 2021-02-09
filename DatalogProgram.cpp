#include "DatalogProgram.h"

#include <sstream>
#include <set>

std::string DatalogProgram::toString() {
    std::stringstream ss;
    ss << "Schemes(" << schemes.size() << "):\n";
    for (auto a : schemes) {
        ss << "  " << a->toString() << '\n';
    }

    ss << "Facts(" << facts.size() << "):\n";
    for (auto a : facts) {
        ss << "  " << a->toString() << "." << '\n';
    }

    ss << "Rules(" << rules.size() << "):\n";
    for (auto a : rules) {
        ss << "  " << a->toString() << '\n';
    }

    ss << "Queries(" << queries.size() << "):\n";
    for (auto a : queries) {
        ss << "  " << a->toString() << "?" << '\n';
    }

    std::set<std::string> domain;
    for (auto a : facts) {
        for (auto p : a->parameters) {
            domain.insert(p->toString());
        }
    }

    ss << "Domain(" << domain.size() << "):\n";
    for (auto a : domain) {
        ss << "  " << a << '\n';
    }

    return ss.str();
}
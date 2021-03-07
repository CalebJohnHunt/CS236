#pragma once

#include <vector>
#include <string>

class Tuple {
public:
    Tuple();
    Tuple(std::vector<std::string>&);
    
    std::vector<std::string> values;
    bool operator< (const Tuple & other) const;

    std::string toString();

private:


};
#pragma once

#include <vector>
#include <string>

class Header {
public:
    Header();
    Header(std::vector<std::string>& attributes);
    std::vector<std::string> attributes;

    std::string toString();

private:


};
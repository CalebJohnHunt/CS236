#pragma once

#include <vector>

#include "Token.h"
#include "DatalogProgram.h"


class Parser {
public:
    Parser(std::vector<Token*> tokens);
    void Parse();


private:
    std::vector<Token*> tokens;
    size_t index = 0;

    bool Match(Token::TokenType);

    void ParseDatalogProgram();
    void ParseSchemeList();
    void ParseFactList();
    void ParseRuleList();
    void ParseQueryList();
    void ParseScheme();
    void ParseFact();
    void ParseRule();
    void ParseQuery();
    void ParseHeadPredicate();
    Predicate* ParsePredicate();
    void ParsePredicateList();
    std::vector<Parameter*> ParseParameterList();
    void ParseStringList();
    void ParseIdList();
    Parameter* ParseParameter();
    std::string ParseExpression();
    void ParseOperator();
};
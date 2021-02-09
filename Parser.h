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

    DatalogProgram* ParseDatalogProgram();
    std::vector<Predicate*> ParseSchemeList();
    std::vector<Predicate*> ParseFactList();
    std::vector<Rule*> ParseRuleList();
    std::vector<Predicate*> ParseQueryList();
    Predicate* ParseScheme();
    Predicate* ParseFact();
    Rule* ParseRule();
    Predicate* ParseQuery();
    Predicate* ParseHeadPredicate();
    Predicate* ParsePredicate();
    std::vector<Predicate*> ParsePredicateList();
    std::vector<Parameter*> ParseParameterList();
    std::vector<Parameter*> ParseStringList();
    std::vector<Parameter*> ParseIdList();
    Parameter* ParseParameter();
    std::string ParseExpression();
    void ParseOperator();
};
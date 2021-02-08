#pragma once

#include <vector>

#include "Token.h"
// #include "Predicate.h"


class Parser {
public:
    Parser(std::vector<Token*> tokens);
    void Parse();


private:
    std::vector<Token*> tokens;
    size_t index = 0;

    // std::vector<Predicate*> schemes;
    // std::vector<Predicate*> facts;
    // std::vector<Predicate*> queries;
    // std::vector<Predicate*> rules;

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
    void ParsePredicate();
    void ParsePredicateList();
    void ParseParameterList();
    void ParseStringList();
    void ParseIdList();
    void ParseParameter();
    void ParseExpression();
    void ParseOperator();
};
#include "Parser.h"

#include <iostream>
#include "string.h"

Parser::Parser(std::vector<Token*> tokens) {
    this->tokens = tokens;
}

Parser::~Parser() {
}

DatalogProgram* Parser::Parse() {

    try {
        this->d = ParseDatalogProgram();
    }
    catch (const char* expected) {
        // Memory leak here. Since we allocate DatalogProgram in ParseDatalogProgram, we have to 
        // somehow get that pointer out, but we can't get the pointer along with a thrown exception. Oh well

        // std::cout << "Exception: expected " << expected << " got " << tokens[index]->name << std::endl;
        std::cout << "Failure!" << "\n  " << tokens[index]->toString() << '\n';
        d = NULL;
    }

    return d;
}


bool Parser::Match(Token::TokenType type) {
    if (tokens[index]->type == type) {
        index++;
        return true;
    }
    return false;
}

// datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
DatalogProgram* Parser::ParseDatalogProgram() {
    DatalogProgram* d = new DatalogProgram();
    if (!Match(Token::SCHEMES))
        throw "Scheme";
    if (!Match(Token::COLON))
        throw ":";
    d->schemes.push_back(ParseScheme());
    for (auto a : ParseSchemeList()) {
        d->schemes.push_back(a);
    }
    if (!Match(Token::FACTS))
        throw "Facts";
    if (!Match(Token::COLON))
        throw ":";
    for (auto a : ParseFactList()) {
        d->facts.push_back(a);
    }
    if (!Match(Token::RULES))
        throw "Rules";
    if (!Match(Token::COLON))
        throw ":";
    for (auto a : ParseRuleList()) {
        d->rules.push_back(a);
    }
    if (!Match(Token::QUERIES))
        throw "Queries";
    if (!Match(Token::COLON))
        throw ":";
    d->queries.push_back(ParseQuery());
    for (auto a : ParseQueryList()) {
        d->queries.push_back(a);
    }
    if (!Match(Token::END))
        throw "EOF";
    return d;
}

// schemeList	->	scheme schemeList | lambda
std::vector<Predicate> Parser::ParseSchemeList() {
    std::vector<Predicate> p;
    try {
        p.push_back(ParseScheme());
    }
    catch (const char* e) { // Must be lambda
        return p;
    }
    std::vector<Predicate> l = ParseSchemeList();
    p.insert(p.end(), l.begin(), l.end());
    return p;
}

// factList	->	fact factList | lambda
std::vector<Predicate> Parser::ParseFactList() {
    std::vector<Predicate> p;
    try {
        p.push_back(ParseFact());
    }
    catch (const char* e) {
        // Throw for some reason
        // Perhaps because it's the final one in the list? FOLLOW(fact) = {ID}
        if (strcmp(e,"Id") == 0)
            return p;
        // Nope, just bad input
        throw e;
    }
    std::vector<Predicate> l = ParseFactList();
    p.insert(p.end(), l.begin(), l.end());
    return p;
}
// ruleList	->	rule ruleList | lambda
std::vector<Rule> Parser::ParseRuleList() {
    std::vector<Rule> r;
    try {
        r.push_back(ParseRule());
    }
    catch (const char* e) {
        // Throw for some reason
        // Perhaps because it's the final one in the list? FOLLOW(rule) = {ID}
        if (strcmp(e,"Id") == 0)
            return r;
        // Nope, just bad input
        throw e;
    }
    std::vector<Rule> l = ParseRuleList();
    r.insert(r.end(), l.begin(), l.end());
    return r;
}

// queryList	->	query queryList | lambda
std::vector<Predicate> Parser::ParseQueryList() {
    std::vector<Predicate> p;
    try {
        p.push_back(ParseQuery());
    }
    catch (const char* e) { // Must be lambda
        if (strcmp(e, "?") == 0)
            throw "?";
        return p;
    }
    std::vector<Predicate> l = ParseQueryList();
    p.insert(p.end(), l.begin(), l.end());
    return p;
}

// scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
// id (id, idlist)
Predicate Parser::ParseScheme() {
    Predicate p = Predicate(tokens[index]->name);
    if (!Match(Token::ID))
        throw "Id";
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    p.AddParameter(new IdParameter(tokens[index]->name));
    if (!Match(Token::ID))
        throw "Id";
    for (auto a : ParseIdList()) {
        p.AddParameter(a);
    }
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
    
    return p;
}

// fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
// id('string', 'stringlist').
Predicate Parser::ParseFact() {
    Predicate p = Predicate(tokens[index]->name);
    if (!Match(Token::ID))
        throw "Id";
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    p.AddParameter(new StringParameter(tokens[index]->name));
    if (!Match(Token::STRING))
        throw "String";
    for (auto a : ParseStringList()) {
        p.AddParameter(a);
    }
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
    if (!Match(Token::PERIOD))
        throw ".";
    return p;
}

// rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
// id (id, idlist) :- id ('param', paramlist) predicatelist.
Rule Parser::ParseRule() {
    Rule r = Rule(ParseHeadPredicate());
    if (!Match(Token::COLON_DASH))
        throw ":-";
    r.AddPredicate(ParsePredicate());
    for (auto a : ParsePredicateList()) {
        r.AddPredicate(a);
    }
    if (!Match(Token::PERIOD))
        throw ".";
    return r;
}

// query	        ->      predicate Q_MARK
// id ('param', paramlist)?
Predicate Parser::ParseQuery() {
    Predicate p = ParsePredicate();
    if (!Match(Token::Q_MARK))
        throw "?";
    return p;
}

Predicate Parser::ParseHeadPredicate() {
    Predicate p = Predicate(tokens[index]->name);
    if (!Match(Token::ID))
        throw "Id";
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    p.AddParameter(new IdParameter(tokens[index]->name));
    if (!Match(Token::ID))
        throw "Id";
    for (auto a : ParseIdList()) {
        p.AddParameter(a);
    }
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
    return p;
}

Predicate Parser::ParsePredicate() {
    Predicate p = Predicate(tokens[index]->name);
    if (!Match(Token::ID))
        throw "Id";
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    p.AddParameter(ParseParameter());
    for (auto a : ParseParameterList()) {
        p.AddParameter(a);
    }
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
    
    return p;
}

std::vector<Predicate> Parser::ParsePredicateList() {
    std::vector<Predicate> p;
    if (Match(Token::COMMA)) {
        p.push_back(ParsePredicate());
        std::vector<Predicate> l = ParsePredicateList();
        p.insert(p.end(), l.begin(), l.end());
    }
    return p;
}

std::vector<Parameter*> Parser::ParseParameterList() {
    std::vector<Parameter*> p;
    if (Match(Token::COMMA)) {
        p.push_back(ParseParameter());
        std::vector<Parameter*> l = ParseParameterList();
        p.insert(p.end(), l.begin(), l.end());
    }
    return p;
}

std::vector<StringParameter*> Parser::ParseStringList() {
    std::vector<StringParameter*> p;
    if (Match(Token::COMMA)) {
        p.push_back(new StringParameter(tokens[index]->name));
        if (!Match(Token::STRING))
            throw "String";
        std::vector<StringParameter*> l = ParseStringList();
        p.insert(p.end(), l.begin(), l.end());
    }
    return p;
}

std::vector<IdParameter*> Parser::ParseIdList() {
    std::vector<IdParameter*> p;
    if (Match(Token::COMMA)) {
        p.push_back(new IdParameter(tokens[index]->name));
        if (!Match(Token::ID))
            throw "Id";
        std::vector<IdParameter*> l = ParseIdList();
        p.insert(p.end(), l.begin(), l.end());
    }
    return p;
}

Parameter* Parser::ParseParameter() {
    if (Match(Token::STRING))
        return new StringParameter(tokens[index-1]->name);
    else if (Match(Token::ID))
        return new IdParameter(tokens[index-1]->name);
    else
        return ParseExpression();
    // return Parameter(s);
    // return new Parameter(ParseExpression());
    
}

ExpressionParameter* Parser::ParseExpression() {
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    Parameter* l = ParseParameter();
    char o = ParseOperator();
    Parameter* r = ParseParameter();
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
    return new ExpressionParameter(l, o, r);
}

char Parser::ParseOperator() {
    if (Match(Token::ADD))
        return '+';
    else if (Match(Token::MULTIPLY))
        return '*';
    throw "+ or *";
}

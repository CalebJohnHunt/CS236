#include "Parser.h"

#include <iostream>
#include "string.h"

Parser::Parser(std::vector<Token*> tokens) {
    this->tokens = tokens;
}

void Parser::Parse() {
    try {
        ParseDatalogProgram();
        std::cout << "\n\nSuccess\n";
    }
    catch (const char* expected) {
        std::cout << "Exception: expected " << expected << " got " << tokens[index]->name << std::endl;
    }
}


bool Parser::Match(Token::TokenType type) {
    if (tokens[index]->type == type) {
        index++;
        return true;
    }
    return false;
}

// datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
void Parser::ParseDatalogProgram() {
    if (!Match(Token::SCHEMES))
        throw "Scheme";
    if (!Match(Token::COLON))
        throw ":";
    ParseScheme();
    ParseSchemeList();
    if (!Match(Token::FACTS))
        throw "Facts";
    if (!Match(Token::COLON))
        throw ":";
    ParseFactList();
    if (!Match(Token::RULES))
        throw "Rules";
    if (!Match(Token::COLON))
        throw ":";
    ParseRuleList();
    if (!Match(Token::QUERIES))
        throw "Queries";
    if (!Match(Token::COLON))
        throw ":";
    ParseQuery();
    ParseQueryList();
    if (!Match(Token::END))
        throw "EOF";
}

// schemeList	->	scheme schemeList | lambda
void Parser::ParseSchemeList() {
    try {
        ParseScheme();
    }
    catch (const char* e) { // Must be lambda
        return;
    }
    ParseSchemeList();
}

// factList	->	fact factList | lambda
void Parser::ParseFactList() {
    try {
        ParseFact();
    }
    catch (const char* e) {
        // Throw for some reason
        // Perhaps because it's the final one in the list? FOLLOW(fact) = {ID}
        if (strcmp(e,"Id") == 0)
            return;
        // Nope, just bad input
        throw e;
    }
    ParseFactList();
}
// ruleList	->	rule ruleList | lambda
void Parser::ParseRuleList() {
    try {
        ParseRule();
    }
    catch (const char* e) {
        // Throw for some reason
        // Perhaps because it's the final one in the list? FOLLOW(rule) = {ID}
        if (strcmp(e,"Id") == 0)
            return;
        // Nope, just bad input
        throw e;
    }
    ParseRuleList();
}

// queryList	->	query queryList | lambda
void Parser::ParseQueryList() {
    try {
        ParseQuery();
    }
    catch (const char* e) { // Must be lambda
        return;
    }
    ParseQueryList();
}

// scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
// id (id, idlist)
void Parser::ParseScheme() {
    if (!Match(Token::ID))
        throw "Id";
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    if (!Match(Token::ID))
        throw "Id";
    ParseIdList();
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
}

// fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
// id('string', 'stringlist').
void Parser::ParseFact() {
    if (!Match(Token::ID))
        throw "Id";
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    if (!Match(Token::STRING))
        throw "String";
    ParseStringList();
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
    if (!Match(Token::PERIOD))
        throw ".";

}
// rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
// id (id, idlist) :- id ('param', paramlist) predicatelist.
void Parser::ParseRule() {
    ParseHeadPredicate();
    if (!Match(Token::COLON_DASH))
        throw ":-";
    ParsePredicate();
    ParsePredicateList();
    if (!Match(Token::PERIOD))
        throw ".";
}

// query	        ->      predicate Q_MARK
// id ('param', paramlist)?
void Parser::ParseQuery() {
    ParsePredicate();
    if (!Match(Token::Q_MARK))
        throw "?";
}

void Parser::ParseHeadPredicate() {
    if (!Match(Token::ID))
        throw "Id";
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    if (!Match(Token::ID))
        throw "Id";
    ParseIdList();
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
}

void Parser::ParsePredicate() {
    if (!Match(Token::ID))
        throw "Id";
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    ParseParameter();
    ParseParameterList();
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
}

void Parser::ParsePredicateList() {
    if (Match(Token::COMMA)) {
        ParsePredicate();
        ParsePredicateList();
    }
    return;
}

void Parser::ParseParameterList() {
    if (Match(Token::COMMA)) {
        ParseParameter();
        ParseParameterList();
    }
    return;
}

void Parser::ParseStringList() {
    if (Match(Token::COMMA)) {
        if (!Match(Token::STRING))
            throw "String";
        ParseStringList();
    }
    return;
}

void Parser::ParseIdList() {
    if (Match(Token::COMMA)) {
        if (!Match(Token::ID))
            throw "Id";
        ParseIdList();
    }
    return;
}

void Parser::ParseParameter() {
    if (Match(Token::STRING) || Match(Token::ID)) {
        return;
    }
    ParseExpression();
}

void Parser::ParseExpression() {
    if (!Match(Token::LEFT_PAREN))
        throw "(";
    ParseParameter();
    ParseOperator();
    ParseParameter();
    if (!Match(Token::RIGHT_PAREN))
        throw ")";
}

void Parser::ParseOperator() {
    if (Match(Token::ADD) || Match(Token::MULTIPLY)) {
        return;
    }
    throw "+ or *";
}

#include "Parser.h"

vector<Statement> *Parser::parse() {
    vector<Statement>* programStack;

    getNextToken();
    return programStack;
}

void Parser::getNextToken() {
    currentToken_ = lexer_.getNextToken();
}


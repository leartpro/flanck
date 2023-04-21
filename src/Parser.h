#ifndef PLANCK_PARSER_H
#define PLANCK_PARSER_H

#include <string>
#include <utility>
#include "Token.h"
#include "Lexer.h"
#include "Statement.h"

class Parser
{
public:
    explicit Parser(Lexer& lexer) : lexer_(lexer), currentToken_(Token::Open) {}
    vector<Statement>* parse();
private:
    void getNextToken();
    Lexer &lexer_;
    Token currentToken_;
};
#endif //PLANCK_PARSER_H

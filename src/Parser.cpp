#include "Parser.h"
#include "Stack.h"

vector<Statement> *Parser::parse() {
    vector<Statement>* programStack;
    while (currentToken_ != Token::Eof) {
        bool valueExpected = false;
        bool hasDivider = false;
        vector<Stack> conditions;
        vector<Stack> instructions;
        vector<bool> currentStack;
        while (currentToken_ != Token::Eol) {
            switch (currentToken_) {
                case Token::Open:
                    if(valueExpected) break;
                    valueExpected = true;
                    currentStack.clear();
                    break;
                case Token::Close:
                    if(!valueExpected) break;
                    valueExpected = false;
                    if(!hasDivider) {
                        conditions.emplace_back(Stack(currentStack));
                    } else {
                        instructions.emplace_back(Stack(currentStack));
                    }
                    break;
                case Token::Zero:
                    if(!valueExpected) break;
                    currentStack.push_back(false);
                    break;
                case Token::One:
                    if(!valueExpected) break;
                    currentStack.push_back(true);
                    break;
                case Token::Divider:
                    if(valueExpected) break;
                    if(hasDivider) break;
                    hasDivider = true;
                    valueExpected = false;
                    break;
                default:
                    break;
            }
            getNextToken();
        }
        programStack->emplace_back(Statement(conditions, instructions));
    }
    return programStack;
}

void Parser::getNextToken() {
    currentToken_ = lexer_.getNextToken();
}


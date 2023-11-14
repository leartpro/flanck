#include "Parser.h"
#include "Stack.h"

void Parser::parse() {
    while (currentToken_ != Token::Eof) {
        bool valueExpected = false;
        bool hasDivider = false;
        bool emptyStatement = true; //holds track if a statement contains only empty stacks
        vector<Stack> conditions;
        vector<Stack> instructions;
        vector<bool> currentStack;
        //until ed of current line
        while (currentToken_ != Token::Eol && currentToken_ != Token::Eof) {
            //for current token
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
                        conditions.emplace_back(currentStack);
                    } else {
                        instructions.emplace_back(currentStack);
                    }
                    break;
                case Token::Zero:
                    if(!valueExpected) break;
                    emptyStatement = false;
                    currentStack.push_back(false);
                    break;
                case Token::One:
                    if(!valueExpected) break;
                    emptyStatement = false;
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
        getNextToken();
        //complete empty statements are ignored
        if(!emptyStatement) {
            statements_.emplace_back(conditions, instructions);
            int currentMaxNumStacks = int(max(conditions.size(), instructions.size()));
            maxNumStacks_ = max(currentMaxNumStacks, maxNumStacks_);
        }
    }
}

void Parser::getNextToken() {
    currentToken_ = lexer_.getNextToken();
}

int Parser::getMaxNumStacks() const {
    return maxNumStacks_;
}

vector<Statement> Parser::getStatements() {
    return statements_;
}

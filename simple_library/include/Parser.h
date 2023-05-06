#ifndef FLANCK_PARSER_H
#define FLANCK_PARSER_H

#include <string>
#include <utility>
#include "Token.h"
#include "Lexer.h"
#include "Statement.h"

/**
 * The Parser parses the Tokens into Statements.
 */
class Parser
{
public:

    /**
     * Initializes the Parser with the given Lexer.
     * @param lexer the given Lexer.
     */
    explicit Parser(Lexer& lexer) : lexer_(lexer), currentToken_() {
        this->maxNumStacks_ = 0;
    }

    /**
     * Parses, the Tokens into Statements.
     */
    void parse();

    /**
     * Returns the amount of Stacks, required for the Interpreter.
     * @return the amount of required Stacks.
     */
    int getMaxNumStacks() const;

    /**
     * Returns the parsed Statements.
     * @return the parsed Statements.
     */
    vector<Statement> getStatements();
private:

    /**
     * Sets the current token to the next Token.
     */
    void getNextToken();

    vector<Statement> statements_;
    Lexer &lexer_;
    Token currentToken_;
    int maxNumStacks_;
};
#endif //FLANCK_PARSER_H

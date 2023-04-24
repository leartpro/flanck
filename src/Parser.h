#ifndef PLANCK_PARSER_H
#define PLANCK_PARSER_H

#include <string>
#include <utility>
#include "Token.h"
#include "Lexer.h"
#include "Statement.h"

/**
 *
 */
class Parser
{
public:

    /**
     *
     * @param lexer
     */
    explicit Parser(Lexer& lexer) : lexer_(lexer), currentToken_(Token::Open) {
        this->maxNumStacks_ = 0;
    }

    /**
     *
     */
    void parse();

    /**
     *
     * @return
     */
    int getMaxNumStacks() const;

    /**
     *
     * @return
     */
    vector<Statement> getStatements();
private:

    /**
     *
     */
    void getNextToken();
    vector<Statement> statements_;
    Lexer &lexer_;
    Token currentToken_;
    int maxNumStacks_;
};
#endif //PLANCK_PARSER_H

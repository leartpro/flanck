#ifndef PLANCK_LEXER_H
#define PLANCK_LEXER_H

#include <string>
#include <utility>
#include "Token.h"

/**
 *
 */
class Lexer
{
public:

    /**
     *
     * @param input
     */
    explicit Lexer(const char* input) : input_(input), position_(0) {}

    /**
     *
     * @return
     */
    Token getNextToken();
private:
    int position_;
    std::string input_;
};
#endif //PLANCK_LEXER_H

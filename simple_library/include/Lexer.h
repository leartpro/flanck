#ifndef FLANCK_LEXER_H
#define FLANCK_LEXER_H

#include <string>
#include <utility>
#include "Token.h"

/**
 * The Lexer contains methods to tokenize the program code.
 */
class Lexer
{
public:

    /**
     * Initializes the Lexer with the given program code.
     * @param input the given program code.
     */
    explicit Lexer(const char* input) : input_(input), position_(0) {}

    /**
     * Returns the current Token and increases the position.
     * @return the current Token.
     */
    Token getNextToken();
private:
    int position_;
    std::string input_;
};
#endif //FLANCK_LEXER_H

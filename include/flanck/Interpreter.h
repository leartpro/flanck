#ifndef PLANCK_INTERPRETER_H
#define PLANCK_INTERPRETER_H

#include <string>
#include <utility>
#include <unordered_map>
#include "Token.h"
#include "Statement.h"
#include "Parser.h"

/**
 *
 */
class Interpreter
{
public:

    /**
     *
     * @param parser
     * @param stacks
     */
    explicit Interpreter(Parser& parser, vector<Stack>& stacks) : parser_(parser), stacks_(std::move(stacks)) {};

    /**
     *
     */
    void interpret();

    /**
     *
     * @return
     */
    Stack getOutputStack();
private:
    Parser &parser_;
    vector<Stack> stacks_;
};
#endif //PLANCK_INTERPRETER_H

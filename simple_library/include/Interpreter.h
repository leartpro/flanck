#ifndef FLANCK_INTERPRETER_H
#define FLANCK_INTERPRETER_H

#include <string>
#include <utility>
#include <unordered_map>
#include "Token.h"
#include "Statement.h"
#include "Parser.h"

/**
 * The Interpreter interprets the Statements.
 */
class Interpreter
{
public:

    /**
     * Initializes the Interpreter with the Parser and the Stacks.
     * @param parser
     * @param stacks
     */
    explicit Interpreter(Parser& parser, vector<Stack>& stacks) : parser_(parser), stacks_(std::move(stacks)) {};

    /**
     * Interprets the statements and applies them to the stacks in the process.
     */
    void interpret();

    /**
     * Returns always the first Stack.
     * @return a Stack, containing the program Output.
     */
    Stack getOutputStack();
private:
    Parser &parser_;
    vector<Stack> stacks_;
};
#endif //FLANCK_INTERPRETER_H

#ifndef FLANCK_AST_H
#define FLANCK_AST_H

#include <string>
#include "Token.h"
#include <utility>
#include <vector>
#include "Stack.h"

using namespace std;
/**
 * A statement contains conditions and instructions.
 */
struct Statement {
    /**
     * Conditions contains the Stacks for the Divider
     * and Instructions the after.
     * @param conditions the conditions for this statement
     * @param instructions the instructions for this statement
     */
    explicit Statement(vector<Stack> conditions, vector<Stack> instructions) {
        this->conditions = std::move(conditions);
        this->instructions = std::move(instructions);
    }
    vector<Stack> conditions, instructions;
};
#endif //FLANCK_AST_H
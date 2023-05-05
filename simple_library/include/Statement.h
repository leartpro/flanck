#ifndef FLANCK_AST_H
#define FLANCK_AST_H

#include <string>
#include "Token.h"
#include <utility>
#include <vector>
#include "Stack.h"

using namespace std;
/**
 *
 */
struct Statement {
    /**
     *
     * @param conditions
     * @param instructions
     */
    explicit Statement(vector<Stack> conditions, vector<Stack> instructions) {
        this->conditions = std::move(conditions);
        this->instructions = std::move(instructions);
    }
    vector<Stack> conditions, instructions;
};
#endif //FLANCK_AST_H
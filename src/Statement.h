#ifndef PLANCK_AST_H
#define PLANCK_AST_H

#include <string>
#include "Token.h"
#include <vector>
#include "Stack.h"

using namespace std;

struct Statement {
    explicit Statement(vector<Stack> conditions, vector<Stack> instructions) {
        this->conditions = conditions;
        this->instructions = instructions;
    }
    vector<Stack> conditions, instructions;
};
#endif //PLANCK_AST_H
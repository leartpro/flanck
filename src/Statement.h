#ifndef PLANCK_AST_H
#define PLANCK_AST_H

#include <string>
#include "Token.h"
#include <vector>

using namespace std;

struct Statement {
    vector<Stack> conditions, instructions;
};
#endif //PLANCK_AST_H
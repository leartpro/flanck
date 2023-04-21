#ifndef PLANCK_INTERPRETER_H
#define PLANCK_INTERPRETER_H

#include <string>
#include <utility>
#include <unordered_map>
#include "Token.h"
#include "Statement.h"

class Interpreter
{
public:
    Interpreter() = default;
    void interpret(vector<Statement>* programStack);
private:
    vector<Stack> stacks_;
};
#endif //PLANCK_INTERPRETER_H

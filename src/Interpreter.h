#ifndef PLANCK_INTERPRETER_H
#define PLANCK_INTERPRETER_H

#include <string>
#include <utility>
#include <unordered_map>
#include <set>
#include "Statement.h"
#include "Parser.h"

class InterpreterObserver
{
public:
    InterpreterObserver() = default;
    inline bool inputAsk();
};

struct StackOption {
    bool onlyAdd;
    bool onlyTake;
    bool shouldNotifyRead;
};

struct InterpreterOptions {
    const int readCount;
    const bool notifyBytes;
    const int maxCount;
    const bool resetCountAfterSuccessfulInputAsk;
    const unordered_map<int, StackOption>;

};

class Interpreter
{
public:
    explicit Interpreter(Parser& parser) : parser_(parser) {};
    void interpret(vector<Statement>* statements);
    vector<Statement> getStacks();
private:
    Parser &parser_;
    vector<Stack> stacks_;
    InterpreterOptions options_;
};
#endif //PLANCK_INTERPRETER_H
#include "Interpreter.h"

void Interpreter::interpret(vector<Statement>* statements) {
    bool stackChanged;
    do {
        stackChanged = false;
        for (const Statement& statement: *statements) {
            for(int i = 0; i < statement.conditions.size(); i++) {
                if (!stacks_[i].endsWith(statement.conditions[i])) {
                    goto next_statement;
                }
            }
            // because no Statements are added that don't read and write, if the
            stackChanged = true;
            for(int i = 0; i < statement.conditions.size(); i++) {
                stacks_[i].remove(statement.conditions[i]);
            }
            for(int i = 0; i < statement.instructions.size(); i++) {
                stacks_[i].push(statement.instructions[i]);
            }
            next_statement:;
        }
    } while (stackChanged);
}
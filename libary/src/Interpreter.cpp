#include "flanck/Interpreter.h"

/**
 *
 */
void Interpreter::interpret() {
    parser_.parse();
    vector<Statement> statements = parser_.getStatements();
    stacks_.resize(parser_.getMaxNumStacks());
    bool stackChanged;
    do {
        stackChanged = false;
        for (const Statement& statement: statements) {
            for(int i = 0; i < statement.conditions.size(); i++) {
                if(statement.conditions[i].isEmpty()) {
                    continue;
                }
                if (!stacks_[i].endsWith(statement.conditions[i])) {
                    goto next_statement;
                }
            }
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

/**
 *
 * @return
 */
Stack Interpreter::getOutputStack() {
    return stacks_[0];
}

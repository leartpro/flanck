#include "Interpreter.h"

void Interpreter::interpret() {
    //initialize statements and stacks
    parser_.parse();
    vector<Statement> statements = parser_.getStatements();
    stacks_.resize(parser_.getMaxNumStacks());
    //while changes are made on stacks
    bool stackChanged;
    do {
        stackChanged = false;
        for (const Statement& statement: statements) {
            for(int i = 0; i < statement.conditions.size(); i++) {
                //if stack in condition is emtpy, skip this stack
                if(statement.conditions[i].isEmpty()) {
                    continue;
                }
                //if the condition is not met
                if (!stacks_[i].endsWith(statement.conditions[i])) {
                    goto next_statement;
                }
            }
            stackChanged = true;
            //remove the read con from the stacks
            for(int i = 0; i < statement.conditions.size(); i++) {
                stacks_[i].remove(statement.conditions[i].height());
            }
            //execute instructions
            for(int i = 0; i < statement.instructions.size(); i++) {
                stacks_[i].push(statement.instructions[i]);
            }
            next_statement:;
        }
    } while (stackChanged);
}

Stack Interpreter::getOutputStack() {
    return stacks_[0];
}

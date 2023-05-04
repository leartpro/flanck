#include "Interpreter.h"

void Interpreter::start() {
    vector<Statement> statements = parser_.getStatements();
    resetCountTillEnd();
    countTillReadAsk = options_.readCount;
    countTillWriteNotification_ = options_.writeNotificationCount;
    forceEnd_ = false;
    bool stackChanged;
    bool newNotification = false;
    do {
        countTillEnd_--;
        stackChanged = false;
        for (const auto &statement: statements) {
            for (int i = 0; i < statement.conditions.size(); i++) {
                if (!stacks_[i].endsWith(statement.conditions[i])) {
                    goto next_statement;
                }
            }
            // because no Statements are added that don't read and write, if the
            stackChanged = true;
            for (int i = 0; i < statement.conditions.size(); i++) {
                stacks_[i].remove(statement.conditions[i]);
                if (!stacks_[i].isEmpty() && notificationMap_[i] == InternNotificationChangeType_::change_) {
                    newNotification = true;
                    change_.changeMap[i] = true;
                }
            }
            for (int i = 0; i < statement.instructions.size(); i++) {
                stacks_[i].push(statement.instructions[i]);
                if (!stacks_[i].isEmpty() && notificationMap_[i] == InternNotificationChangeType_::newBytesChange_) {
                    auto &addedChangeMap = change_.byteAddChangeMap[i];
                    addedChangeMap.push(statement.instructions[i]);
                    if(addedChangeMap.moreThanAByteLength()) {
                        change_.changeMap[i] = true;
                        newNotification = true;
                    }
                }
            }
            next_statement:;
        }
        if (countTillWriteNotification_-- == 0) {
            countTillWriteNotification_ = options_.writeNotificationCount;
            if (newNotification) {
                observer_.change(this);
                change_.resetChangeStack();
                newNotification = false;
            }
        }
        if (countTillReadAsk-- == 0) {
            observer_.inputAsk(this);
            countTillReadAsk = options_.readCount;
        }
    } while (stackChanged || forceEnd_);
    if (newNotification && !forceEnd_) {
        observer_.change(this);
    }
}

void Interpreter::end() {
    forceEnd_ = true;
}

void Interpreter::resetCountTillEnd() {
    countTillEnd_ = options_.endCount;
}

pair<optional<int>, optional<int>> Interpreter::checkForStackConstraintError() {
    optional<int> readOnly, writeOnly;
    for (auto const &[stackIndex, constraint]: options_.constraints) {
        for (const auto &statement: parser_.getStatements()) {
            if (constraint == StackConstraint::readOnly) {
                if (!readOnly.has_value()) {
                    if (statement.instructions.size() - 1 >= stackIndex &&
                        statement.instructions[stackIndex].isEmpty()) {
                        readOnly = stackIndex;
                    }
                }
            } else if (!writeOnly.has_value()) {
                if (statement.conditions.size() - 1 >= stackIndex &&
                    statement.conditions[stackIndex].isEmpty()) {
                    writeOnly = stackIndex;
                }
            }
        }
    }
    return {readOnly, writeOnly};
}

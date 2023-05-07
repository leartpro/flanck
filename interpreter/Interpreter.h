#ifndef PLANCK_INTERPRETER_H
#define PLANCK_INTERPRETER_H

#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>
#include <thread>
#include "Statement.h"
#include "Parser.h"

enum NotificationChangeType {
    onAllChanges,
    onNewByteChange,
};

enum InternNotificationChangeType_ {
    none_ = 0,
    change_ = 1,
    newBytesChange_ = 2,
};

enum StackConstraint {
    readOnly,
    writeOnly,
};

enum InterpreterEndReason {
    standard,
    forceEnd,
    tooMuchOutput,
    tooManyCycles,
};

struct InterpreterOptions {
    InterpreterOptions(int readCount, int endCount,
                       int writeNotificationCount,
                       int minStackLength,
                       int outputLimit,
                       unordered_map<int, StackConstraint> &constraints,
                       unordered_map<int, NotificationChangeType> &notifications) :
            readCount(readCount), endCount(endCount), writeNotificationCount(writeNotificationCount),
            minStackLength(minStackLength), constraints(constraints),
            notifications(notifications), outputLimit(outputLimit) {}

    const int readCount;
    const int writeNotificationCount;
    const int endCount;
    const int minStackLength;
    const int outputLimit;
    const unordered_map<int, StackConstraint> constraints;
    const unordered_map<int, NotificationChangeType> notifications;

};

struct StackChange {
    vector<bool> changeMap;
    vector<Stack> byteAddChangeMap;

    void resetChangeStack() {
        fill(changeMap.begin(), changeMap.end(), false);
        for(auto& a : byteAddChangeMap) {
            a.clear();
        }
    }
};

class Interpreter;

class InterpreterObserver {
public:
    InterpreterObserver() = default;

    virtual void started(Interpreter *interpreter) = 0;

    virtual void inputAsk(Interpreter *interpreter) = 0;

    virtual void change(Interpreter *interpreter) = 0;

    virtual void ended(Interpreter *interpreter) = 0;
};


class Interpreter {
public:
    explicit Interpreter(Parser &parser, InterpreterObserver &observer, InterpreterOptions options) : parser_(parser),
                                                                                                      observer_(
                                                                                                              observer),
                                                                                                      options_(std::move(
                                                                                                              options)) {
        int stackLength = getStackLength();
        change_.changeMap = vector<bool>(stackLength);
        change_.byteAddChangeMap = vector<Stack>(stackLength, Stack(vector<bool>()));
        notificationMap_ = new InternNotificationChangeType_[stackLength];
        stacks_.resize(stackLength);
        for(int i = 0; i < stackLength; i++) {
            notificationMap_[i] = InternNotificationChangeType_::none_;
        }
        for (auto [stackIndex, notificationChangeType]: options_.notifications) {
            notificationMap_[stackIndex] = _notificationChangeToIntern(notificationChangeType);
        }
    };

    InternNotificationChangeType_ _notificationChangeToIntern(NotificationChangeType notificationChange) {
        if(notificationChange == NotificationChangeType::onAllChanges) {
            return InternNotificationChangeType_::change_;
        } else {
            return InternNotificationChangeType_::newBytesChange_;
        }
        return InternNotificationChangeType_::none_;
    }

    int getStackLength() {
        auto stackLength = max(parser_.getMaxNumStacks(), options_.minStackLength);
        for (auto const &[stackIndex, _]: options_.constraints) {
            stackLength = max(stackLength, stackIndex + 1);
        }
        for (auto const &[stackIndex, _]: options_.notifications) {
            stackLength = max(stackLength, stackIndex + 1);
        }
        return stackLength;
    }

    InterpreterEndReason run();

    void end();

    void resetCountTillEnd();

    pair<optional<int>, optional<int>> checkForStackConstraintError();

    StackChange getStackChange() {
        return change_;
    }

    Stack getStack(int i) {
        return stacks_[i];
    }

    void pushStack(int i, Stack s) {
        stacks_[i].push(std::move(s));
    }

    void replaceStack(int i, Stack s) {
        stacks_[i] = std::move(s);
    }

private:
    InterpreterObserver &observer_;
    Parser &parser_;
    vector<Stack> stacks_;
    InterpreterOptions options_;
    StackChange change_;
    int countTillReadAsk = 0;
    int countTillEnd_ = 0;
    int countTillWriteNotification_ = 0;
    bool forceEnd_ = false;
    InternNotificationChangeType_* notificationMap_;
};



#endif //PLANCK_INTERPRETER_H
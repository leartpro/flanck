#ifndef PLANCK_INTERPRETER_H
#define PLANCK_INTERPRETER_H

#include <string>
#include <utility>
#include <unordered_map>
#include <set>
#include "Statement.h"
#include "Parser.h"

enum NotificationChange {
    onAllChanges,
    onNewByteChange,
};

enum _InternNotificationChange {
    none_ = 0,
    change_ = 1,
    newBytesChange_ = 2,
};

enum StackConstraint {
    readOnly,
    writeOnly,
};

struct InterpreterOptions {
    InterpreterOptions(int readCount, int endCount,
                       int writeNotificationCount,
                       int minStackLength,
                       unordered_map<int, StackConstraint> &constraints,
                       unordered_map<int, NotificationChange> &notifications) :
            readCount(readCount), endCount(endCount), writeNotificationCount(writeNotificationCount),
            minStackLength(minStackLength), constraints(constraints),
            notifications(notifications) {}

    const int readCount;
    const int writeNotificationCount;
    const int endCount;
    const int minStackLength;
    const unordered_map<int, StackConstraint> constraints;
    const unordered_map<int, NotificationChange> notifications;

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
    virtual inline void inputAsk(Interpreter *interpreter);

    virtual inline void change(Interpreter *interpreter);
};

class Interpreter {
public:
    explicit Interpreter(Parser &parser, InterpreterObserver &observer, InterpreterOptions options) : parser_(parser),
                                                                                                      observer_(
                                                                                                              observer),
                                                                                                      options_(
                                                                                                              options) {
        int stackLength = getStackLength();
        change_.changeMap = vector<bool>(stackLength);
        change_.byteAddChangeMap = vector<Stack>(stackLength, Stack(vector<bool>()));
        notificationMap_ = new _InternNotificationChange[stackLength];
        // TODO: funktioniert???
        for (auto [stackIndex, notificationChangeType]: options_.notifications) {
            notificationMap_[stackIndex] = _notificationChangeToIntern(notificationChangeType);
        }
    };

    _InternNotificationChange _notificationChangeToIntern(NotificationChange notificationChange) {
        if(notificationChange == NotificationChange::onAllChanges) {
            return _InternNotificationChange::change_;
        } else {
            return _InternNotificationChange::newBytesChange_;
        }
        return _InternNotificationChange::none_;
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

    void start();

    void end();

    void resetCountTillEnd();

    pair<optional<int>, optional<int>> checkForStackConstraintError();

    StackChange getStackChange() {
        return change_;
    }

private:
    InterpreterObserver &observer_;
    Parser &parser_;
    vector<Stack> stacks_;
    InterpreterOptions options_;
    StackChange change_;
    int countTillReadAsk;
    int countTillEnd_;
    int countTillWriteNotification_;
    bool forceEnd_;
    _InternNotificationChange* notificationMap_;
};


#endif //PLANCK_INTERPRETER_H
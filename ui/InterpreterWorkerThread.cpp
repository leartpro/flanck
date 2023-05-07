//
// Created by Tony Borchert on 07.05.23.
//

#include "InterpreterWorkerThread.h"

void InterpreterWorkerThread::run() {
    auto s = programCode.c_str();
    Lexer lexer(s);
    Parser parser(lexer);
    parser.parse();
    unordered_map<int, StackConstraint> constraints = {};
    unordered_map<int, NotificationChangeType> notifications = {{1, NotificationChangeType::onNewByteChange}};
    InterpreterOptions options(10, 100000000, 10, 2, 1000*8, constraints, notifications);
    Interpreter interpreter(parser, *this, options);
    auto initialStack = Stack::fromBinaryString(binaryInitialInput.toStdString());
    interpreter.replaceStack(0, initialStack);
    auto endReason = interpreter.run();
    if(!isInterruptionRequested()) {
        emit end(endReason);
    }
    // TODO: deleting?????
    //delete [] s;
    //delete this;
}

InterpreterWorkerThread::InterpreterWorkerThread(const QString &programCode, const QString& binaryInitialInput) : programCode(programCode.toStdString()),
                                                                               binaryInitialInput(binaryInitialInput), newInput(false) {

}

void InterpreterWorkerThread::input(const QString& s) {
    inputMutex.lock();
    if(newInput) {
        string sStd = s.toStdString();
        reverse(sStd.begin(), sStd.end());
        inputString = sStd + inputString;
    } else {
        newInput = true;
        inputString = s.toStdString();
        reverse(inputString.begin(), inputString.end());
    }
    inputMutex.unlock();
}

void InterpreterWorkerThread::change(Interpreter *interpreter) {
    if(this->isInterruptionRequested()) {
        return;
    }
    const string o = interpreter->getStackChange().byteAddChangeMap[1].toString();
    emit output(QString::fromStdString(o));
}

void InterpreterWorkerThread::inputAsk(Interpreter *interpreter) {
    if(this->isInterruptionRequested()) {
        interpreter->end();
        return;
    }
    if(inputMutex.try_lock()) {
        if(newInput) {
            Stack newStack = Stack::fromString(inputString);
            Stack oldStack = interpreter->getStack(0);
            newStack.push(oldStack);
            interpreter->replaceStack(0, newStack);
            newInput = false;
        }
        inputMutex.unlock();
    }
}

void InterpreterWorkerThread::started(Interpreter *interpreter) {}

void InterpreterWorkerThread::ended(Interpreter *interpreter) {}

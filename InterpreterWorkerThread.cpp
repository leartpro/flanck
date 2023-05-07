//
// Created by Tony Borchert on 07.05.23.
//

#include "InterpreterWorkerThread.h"

void InterpreterWorkerThread::run() {
}

InterpreterWorkerThread::InterpreterWorkerThread(const QString &programCode) : programCode(programCode.toStdString()),
                                                                               newInput(false) {

}

void InterpreterWorkerThread::input(const QString& s) {
    inputMutex.lock();
    newInput = true;
    inputString = s.toStdString();
    inputMutex.unlock();
}

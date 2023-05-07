//
// Created by Tony Borchert on 07.05.23.
//

#ifndef FLANCK_GUI_INTERPRETERWORKERTHREAD_H
#define FLANCK_GUI_INTERPRETERWORKERTHREAD_H


#include <QThread>
#include <QMutex>
#include "../interpreter/Interpreter.h"

class InterpreterWorkerThread : public QThread, public InterpreterObserver {
    Q_OBJECT

public: explicit InterpreterWorkerThread(const QString& programCode);

private:

    void run() override;

public:
    void end(Interpreter *interpreter) override;
    void start(Interpreter *interpreter) override;

    void input(const QString& s);
    void change(Interpreter *interpreter) override;
    void inputAsk(Interpreter *interpreter) override;

        signals:
    void output(const QString& s);
    //void finished();

private:
    QMutex inputMutex;
    bool newInput;
    std::string inputString;
    std::string programCode;
};


#endif //FLANCK_GUI_INTERPRETERWORKERTHREAD_H

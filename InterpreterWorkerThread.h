//
// Created by Tony Borchert on 07.05.23.
//

#ifndef FLANCK_GUI_INTERPRETERWORKERTHREAD_H
#define FLANCK_GUI_INTERPRETERWORKERTHREAD_H


#include <QThread>
#include <QMutex>

class InterpreterWorkerThread : public QThread {
    Q_OBJECT

    InterpreterWorkerThread(const QString& programCode);

    void run() override;

public:
    void input(const QString& s);
signals:
    void output(const QString& s);

private:
    QMutex inputMutex;
    bool newInput;
    std::string inputString;
    std::string programCode;
};


#endif //FLANCK_GUI_INTERPRETERWORKERTHREAD_H

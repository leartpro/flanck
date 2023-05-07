#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QPlainTextEdit>
#include "widgets/OnlyWriteLineEdit.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget *button;
    QLabel *outputLabel;
    OnlyWriteLineEdit *inputEdit;
    QScrollArea *scrollArea;
    QPlainTextEdit *textEdit;
    QThread* currentWorker;

    int refreshFrameTimerId;

    bool isMaxVertical;
    bool isMaxHorizontal;
private slots:
    void startProgram();
    void programFinished();
    void newOutput(const QString &s);

protected:
    void timerEvent(QTimerEvent *event) override;

    void refreshFrame();


};

#endif // MAINWINDOW_H
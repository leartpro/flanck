#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include "OnlyWriteLineEdit.h"

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

    int refreshFrameTimerId;
    int readOutputTimerId;

    bool isMaxVertical;
    bool isMaxHorizontal;
private slots:
    void startProgram();

protected:
    void timerEvent(QTimerEvent *event) override;

    void refreshFrame();

    void readOutput();

    void newOutput(const QString &s);
};

#endif // MAINWINDOW_H
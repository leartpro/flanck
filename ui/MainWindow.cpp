#include "MainWindow.h"
#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QObject>
#include <QPlainTextEdit>
#include "widgets/FlanckSyntaxHighlighter.h"
#include "widgets/OnlyWriteLineEdit.h"
#include "InterpreterWorkerThread.h"
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), currentWorker(nullptr) {
    isMaxHorizontal = false;
    isMaxVertical = false;
    setWindowTitle("flanck");

    button = new QPushButton("run flanck code");

    inputEdit = new OnlyWriteLineEdit();

    outputLabel = new QLabel("");
    outputLabel->setScaledContents(true); // TODO: need?
    outputLabel->setContentsMargins(4, 0, 4, 0);
    scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(outputLabel);

    textEdit = new QPlainTextEdit(this);
    new FlanckSyntaxHighlighter(textEdit->document());

    auto *layout = new QGridLayout();
    auto *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);

    layout->addWidget(textEdit, 0, 0);
    layout->addWidget(button, 1, 0);
    layout->addWidget(new QLabel("input:"), 2, 0);
    layout->addWidget(inputEdit, 3, 0);
    layout->addWidget(new QLabel("output"), 4, 0);
    layout->addWidget(scrollArea, 5, 0);

    QObject::connect(button, SIGNAL(released()), this, SLOT(startProgram()));

    refreshFrameTimerId = startTimer(10);
}

MainWindow::~MainWindow() {
    killTimer(refreshFrameTimerId);
}

void MainWindow::timerEvent(QTimerEvent *event) {
    if (event->timerId() == refreshFrameTimerId) {
        refreshFrame();
    }
}

void MainWindow::refreshFrame() {
    int visibleX = isMaxHorizontal ? outputLabel->width() : 0;
    int visibleY = isMaxVertical ? outputLabel->height() : 0;

    if (isMaxHorizontal || isMaxVertical) {
        scrollArea->ensureVisible(visibleX, visibleY, 0, 0);
        isMaxHorizontal = false;
        isMaxVertical = false;
    }
}

void MainWindow::newOutput(const QString &s) {
    QScrollBar *scrollBarHorizontal = scrollArea->horizontalScrollBar();
    QScrollBar *scrollBarVertical = scrollArea->verticalScrollBar();
    isMaxHorizontal = scrollBarHorizontal->value() == scrollBarHorizontal->maximum();
    isMaxVertical = scrollBarVertical->value() == scrollBarVertical->maximum();
    outputLabel->setText(outputLabel->text() + s);
}

void MainWindow::startProgram() {
    if(currentWorker) {
        currentWorker->requestInterruption();
    }

    outputLabel->setText("");
    inputEdit->setText("");
    setWindowTitle("flanck - running");

    currentWorker = new InterpreterWorkerThread(textEdit->toPlainText());
    currentWorker->start();
    connect(currentWorker, SIGNAL(finished()), this, SLOT(programFinished()));
    connect(currentWorker, SIGNAL(output(QString)), this, SLOT(newOutput(QString)));
}

void MainWindow::programFinished() {
    setWindowTitle("flanck - finished");
    currentWorker = nullptr;
}

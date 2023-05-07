#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include <iostream>
#include <QAccessible>
#include <QLabel>
#include "MainWindow.h"

using namespace std;

// class MainWindow : public QMainWindow {
// Q_OBJECT

// public:
//     MainWindow();

// protected:
//     void

// };



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    w.show();
    return QApplication::exec();
}

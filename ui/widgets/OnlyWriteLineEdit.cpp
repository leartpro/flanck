//
// Created by Tony Borchert on 06.05.23.
//

#include <QtGui/qpainter.h>
#include "OnlyWriteLineEdit.h"

OnlyWriteLineEdit::OnlyWriteLineEdit(QWidget *parent) : QLineEdit(parent) {
    auto thickCursor = QCursor();
    setCursor(thickCursor);

}

void OnlyWriteLineEdit::mousePressEvent(QMouseEvent *) {
}

void OnlyWriteLineEdit::mouseDoubleClickEvent(QMouseEvent *) {

}

void OnlyWriteLineEdit::mouseMoveEvent(QMouseEvent *) {

}

void OnlyWriteLineEdit::keyPressEvent(QKeyEvent *k) {
    if (k->key() == Qt::Key_Backspace || k->key() == Qt::Key_Left) {
        return;
    }
    QLineEdit::keyPressEvent(k);
}
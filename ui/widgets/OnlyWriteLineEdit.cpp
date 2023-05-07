//
// Created by Tony Borchert on 06.05.23.
//

#include <QtGui/qpainter.h>
#include "OnlyWriteLineEdit.h"

OnlyWriteLineEdit::OnlyWriteLineEdit(QWidget *parent) : QLineEdit(parent), oldLength(0) {
    auto thickCursor = QCursor();
    setCursor(thickCursor);
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(textHasChanged(QString)));
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

void OnlyWriteLineEdit::textHasChanged(const QString& s) {
    if(s.length() > oldLength) {
        auto changed = s.right(s.length() - oldLength);
        emit addedText(changed);
    }
    oldLength = s.length();
}

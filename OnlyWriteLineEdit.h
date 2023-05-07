//
// Created by Tony Borchert on 06.05.23.
//

#ifndef FLANCK_GUI_ONLYWRITELINEEDIT_H
#define FLANCK_GUI_ONLYWRITELINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>


class OnlyWriteLineEdit : public QLineEdit {

public:
    explicit OnlyWriteLineEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *k) override;

    void mousePressEvent(QMouseEvent *) override;

    void mouseDoubleClickEvent(QMouseEvent *) override;

    void mouseMoveEvent(QMouseEvent *) override;
};


#endif //FLANCK_GUI_ONLYWRITELINEEDIT_H

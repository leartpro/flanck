//
// Created by Tony Borchert on 06.05.23.
//

#ifndef FLANCK_GUI_ONLYWRITELINEEDIT_H
#define FLANCK_GUI_ONLYWRITELINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>


class OnlyWriteLineEdit : public QLineEdit {
    Q_OBJECT

public:
    explicit OnlyWriteLineEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *k) override;

    void mousePressEvent(QMouseEvent *) override;

    void mouseDoubleClickEvent(QMouseEvent *) override;

    void mouseMoveEvent(QMouseEvent *) override;

private:
    int oldLength;
signals:
    void addedText(const QString &);

private slots:
    void textHasChanged(const QString&);

};


#endif //FLANCK_GUI_ONLYWRITELINEEDIT_H

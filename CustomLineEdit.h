#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomLineEdit(QWidget *parent = 0);

signals:
    void sig_focusout();
    void sig_focusin();

protected:
    virtual void focusOutEvent(QFocusEvent *e);
    virtual void focusInEvent(QFocusEvent *e);

public slots:

};

#endif // CUSTOMLINEEDIT_H

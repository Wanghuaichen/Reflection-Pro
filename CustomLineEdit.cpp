#include "CustomLineEdit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void CustomLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit sig_focusout();
}

void CustomLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit sig_focusin();
}

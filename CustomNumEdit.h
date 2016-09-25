#ifndef CUSTOMNUMEDIT_H
#define CUSTOMNUMEDIT_H

#include <QWidget>

#include "CustomLineEdit.h"

namespace Ui {
class CustomNumEdit;
}

class CustomNumEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CustomNumEdit(QString resetString, int min, int max, int count, bool allowZero, QWidget *parent = 0);
    virtual ~CustomNumEdit();
    QString GetText(QString addSign);
    bool IsReset();
    void SetText(QString value);

signals:
    void lostFocus();

protected slots:
    void OnTextChanged();
    void OnLostFocus();
    void OnInFocus();

private:
    Ui::CustomNumEdit *ui;
    CustomLineEdit *m_numEdit;
    QString m_resetString;
    bool m_allowZero;
    int m_min;
    int m_max;
    int m_count;
};

#endif // CUSTOMNUMEDIT_H

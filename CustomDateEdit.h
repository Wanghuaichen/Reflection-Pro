#ifndef CUSTOMDATEEDIT_H
#define CUSTOMDATEEDIT_H
#define YEAR "YYYY"
#define MONTH "MM"
#define DAY "DD"
#define HOUR "HH"
#define MINUTE "MM"

#include "CustomNumEdit.h"

#include <QWidget>
#include <QLabel>

namespace Ui {
class CustomDateEdit;
}

class CustomDateEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CustomDateEdit(bool hasTime, QWidget *parent = 0);
    virtual ~CustomDateEdit();
    void SetDateTime(QString value);
    QDateTime GetDateTime();
    bool isWholeDate();
    bool isResetDate();
    QList<QString> GetAge();


signals:
    void HasFilled();
    void HasCleared();

protected slots:
    void OnLostFocus();

private:
    Ui::CustomDateEdit *ui;
    CustomNumEdit *m_yearEdit;
    CustomNumEdit *m_monthEdit;
    CustomNumEdit *m_dayEdit;
    CustomNumEdit *m_hourEdit;
    CustomNumEdit *m_minuteEdit;



};

#endif // CUSTOMDATEEDIT_H

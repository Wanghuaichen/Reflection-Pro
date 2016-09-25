#include "CustomDateEdit.h"
#include "ui_CustomDateEdit.h"
//#include "StyleManager.h"
#include "CustomNumEdit.h"
#include "EnumPatientGenderItem.h"

#include <QDebug>
#include <QRegExp>
#include <QDate>

CustomDateEdit::CustomDateEdit(bool hasTime, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomDateEdit),
    m_hourEdit(0),
    m_minuteEdit(0)
{
    ui->setupUi(this);
    //StyleManager::GetInstance()->Init((QWidget*)this);

    this->m_yearEdit = new CustomNumEdit(YEAR, 1900, 9999, -1, false);
    this->m_monthEdit = new CustomNumEdit(MONTH, 1, 12, 2, false);
    this->m_dayEdit = new CustomNumEdit(DAY, 1, 31, 2, false);

    this->ui->gridLayout->addWidget(this->m_yearEdit,0,0,1,1);
    this->ui->gridLayout->addWidget(new QLabel("-"),0,1,1,1);
    this->ui->gridLayout->addWidget(this->m_monthEdit,0,2,1,1);
    this->ui->gridLayout->addWidget(new QLabel("-"),0,3,1,1);
    this->ui->gridLayout->addWidget(this->m_dayEdit,0,4,1,1);

    connect(this->m_yearEdit,SIGNAL(lostFocus()),this,SLOT(OnLostFocus()));
    connect(this->m_monthEdit,SIGNAL(lostFocus()),this,SLOT(OnLostFocus()));
    connect(this->m_dayEdit,SIGNAL(lostFocus()),this,SLOT(OnLostFocus()));

    if (hasTime)
    {
        this->m_hourEdit = new CustomNumEdit(HOUR,0,23,2,true);
        this->m_minuteEdit = new CustomNumEdit(MINUTE,0,59,2,true);

        this->ui->gridLayout->addWidget(new QLabel(" "),0,5,1,1);
        this->ui->gridLayout->addWidget(this->m_hourEdit,0,6,1,1);
        this->ui->gridLayout->addWidget(new QLabel(":"),0,7,1,1);
        this->ui->gridLayout->addWidget(this->m_minuteEdit,0,8,1,1);

        connect(this->m_hourEdit,SIGNAL(lostFocus()),this,SLOT(OnLostFocus()));
        connect(this->m_minuteEdit,SIGNAL(lostFocus()),this,SLOT(OnLostFocus()));
    }
}

CustomDateEdit::~CustomDateEdit()
{
    delete ui;
}

void CustomDateEdit::SetDateTime(QString value)
{
    QRegExp regx("\\D");
    QList<QString> valueList = value.split(regx);

    for (int i = 0; i < valueList.count(); i++)
    {
        if (!valueList[i].trimmed().isEmpty())
        {
            switch(i)
            {
            case 0:
                this->m_yearEdit->SetText(valueList[i]);
                break;

            case 1:
                this->m_monthEdit->SetText(valueList[i]);
                break;

            case 2:
                this->m_dayEdit->SetText(valueList[i]);
                break;

            case 3:
                if (this->m_hourEdit != 0)
                {
                    this->m_hourEdit->SetText(valueList[i]);
                }

                break;

            case 4:
                if (this->m_minuteEdit != 0)
                {
                    this->m_minuteEdit->SetText(valueList[i]);
                }

                break;
            }
        }
    }
}

QDateTime CustomDateEdit::GetDateTime()
{
    QDateTime dateTime;

    dateTime.setDate(QDate(this->m_yearEdit->GetText("").toInt(),
                           this->m_monthEdit->GetText("").toInt(),
                           this->m_dayEdit->GetText("").toInt()));

    if (this->m_hourEdit != 0 && this->m_minuteEdit != 0)
    {
        dateTime.setTime(QTime(this->m_hourEdit->GetText("").toInt(),
                               this->m_minuteEdit->GetText("").toInt()));
    }

    return dateTime;
}

bool CustomDateEdit::isWholeDate()
{
    bool whole = (!this->m_yearEdit->GetText("").isEmpty()) &&
                 (this->m_yearEdit->GetText("").length() == 4) &&
                 (!this->m_monthEdit->GetText("").isEmpty()) &&
                 (!this->m_dayEdit->GetText("").isEmpty());

    if (0 != this->m_hourEdit && 0 != this->m_minuteEdit)
    {
        whole = whole && (!this->m_hourEdit->GetText("").isEmpty()) && (!this->m_minuteEdit->GetText("").isEmpty());
    }

    return whole;
}

bool CustomDateEdit::isResetDate()
{
    bool reset = (this->m_yearEdit->IsReset()) &&
                 (this->m_monthEdit->IsReset()) &&
                 (this->m_dayEdit->IsReset());

    if (0 != this->m_hourEdit && 0 != this->m_minuteEdit)
    {
        reset = reset && (this->m_hourEdit->IsReset()) && (this->m_minuteEdit->IsReset());
    }

    return reset;
}

QList<QString> CustomDateEdit::GetAge()
{
    QList<QString> age;
    age.append(" ");
    age.append(QString::number(eYears));

    if (this->isWholeDate())
    {
        QDate today = QDate::currentDate();
        QDate birth(this->m_yearEdit->GetText("").toInt(),this->m_monthEdit->GetText("").toInt(),this->m_dayEdit->GetText("").toInt());
        int days = birth.daysTo(today);

        if (days < 32)
        {
            age[0] = QString::number(days);
            age[1] = QString::number(eDays);
        }
        else if (days < 366)
        {
            int months = days / 30;
            age[0] = QString::number(months);
            age[1] = QString::number(eMonths);
        }
        else
        {
            int years = days / 365;
            age[0] = QString::number(years);
        }
    }

    return age;
}

void CustomDateEdit::OnLostFocus()
{
    bool filled = !this->m_yearEdit->GetText("").isEmpty() ||
                  !this->m_monthEdit->GetText("").isEmpty() ||
                  !this->m_dayEdit->GetText("").isEmpty();

    if (filled)
    {
        emit this->HasFilled();
    }
    else
    {
        emit this->HasCleared();
    }
}

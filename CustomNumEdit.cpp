#include "CustomNumEdit.h"
#include "ui_CustomNumEdit.h"
//#include "StyleManager.h"

#include <QRegExp>
#include <QValidator>

CustomNumEdit::CustomNumEdit(QString resetString, int min, int max, int count, bool allowZero, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomNumEdit)
{
    ui->setupUi(this);
    this->m_resetString = resetString;
    this->m_min = min;
    this->m_max = max;
    this->m_count = count;
    this->m_allowZero = allowZero;
    this->m_numEdit = new CustomLineEdit();
    this->ui->gridLayout->addWidget(this->m_numEdit);
    //StyleManager::GetInstance()->Init((QWidget*)this);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx,this->m_numEdit);
    this->m_numEdit->setValidator(validator);
    this->m_numEdit->setText(this->m_resetString);

    connect(this->m_numEdit,SIGNAL(textChanged(QString)),this,SLOT(OnTextChanged()));
    connect(this->m_numEdit,SIGNAL(sig_focusout()),this,SLOT(OnLostFocus()));
    connect(this->m_numEdit,SIGNAL(sig_focusin()),this,SLOT(OnInFocus()));
}

CustomNumEdit::~CustomNumEdit()
{
    delete ui;
}

QString CustomNumEdit::GetText(QString addSign)
{
    QString value;

    if (this->m_numEdit->text() != this->m_resetString)
    {
        value = this->m_numEdit->text() + addSign;
    }

    return value;
}

bool CustomNumEdit::IsReset()
{
    return (this->m_numEdit->text() == this->m_resetString);
}

void CustomNumEdit::SetText(QString value)
{
    if (!value.isEmpty())
    {
        this->m_numEdit->setText(value);
    }
}

void CustomNumEdit::OnTextChanged()
{
    QString text = this->m_numEdit->text().trimmed();
    if (!text.isEmpty() && text != this->m_resetString)
    {
        bool ok = false;
        int value = text.toInt(&ok);
        if (!ok)
        {
            text = "";
        }
        else if (value > this->m_max)
        {
            value = value / 10;
            text = QString::number(value);
        }
        else if(!this->m_allowZero && value == 0)
        {
            text = "";
        }
        else
        {
            text = QString::number(value);
        }

        this->m_numEdit->setText(text);
    }
}

void CustomNumEdit::OnLostFocus()
{
    QString text = this->m_numEdit->text().trimmed();
    if (text.isEmpty())
    {
        this->m_numEdit->setText(this->m_resetString);
    }
    else if (text != this->m_resetString)
    {
        int value = text.toInt();
        if (value < this->m_min || value > this->m_max)
        {
            this->m_numEdit->setStyleSheet("color:red");
        }
        else if (this->m_count > 0)
        {
            text = text.rightJustified(this->m_count, '0');
            this->m_numEdit->setText(text);
        }
    }

    emit this->lostFocus();
}

void CustomNumEdit::OnInFocus()
{
    this->m_numEdit->setStyleSheet("color:black");
}

#include "ReViewQueryDlg.h"
#include "ui_ReViewQueryDlg.h"
//#include "LanguageManager.h"
//#include "StyleManager.h"
#include "CommonInfomation.h"

#include <QDate>
#include <QLabel>
#include <QSpacerItem>

ReViewQueryDlg::ReViewQueryDlg(QWidget *parent) :
    QDialog(parent),    
    ui(new Ui::ReViewQueryDlg)
{
    ui->setupUi(this);
    //StyleManager::GetInstance()->Init((QWidget*)this);

    this->Init();
    this->InitLanguage();
    this->GenerateQueryCondition();

    this->setWindowFlags(Qt::SubWindow);
    this->ui->btnOK->setFocus();
    this->ui->btnOK->setDefault(true);
}

ReViewQueryDlg::~ReViewQueryDlg()
{
    delete ui;
}

QueryCondition ReViewQueryDlg::GetQuery() const
{
    return this->m_query;
}

void ReViewQueryDlg::OnSave()
{
    this->GenerateQueryCondition();
    this->close();
}

void ReViewQueryDlg::OnCancel()
{
    this->m_query.Clear();
    this->close();
}

void ReViewQueryDlg::InitLanguage()
{
    /*this->setWindowTitle(TR("Query"));
    this->ui->labelSampleID->setText(TR("Sample ID"));
    this->ui->labelName->setText(TR("PatientName"));
    this->ui->labelExamDate->setText(TR("CheckDate"));
    this->ui->labelSampleStatus->setText(TR("Sample Status"));
    this->ui->checkBoxUnvalidated->setText(TR("Unvalidated"));
    this->ui->checkBoxUnprinted->setText(TR("Unprinted"));
    this->ui->checkBoxUnLis->setText(TR("Untransfered"));
    this->ui->btnOK->setText(TR("OK"));
    this->ui->btnCancel->setText(TR("Cancel"));
    this->ui->btnCurUnvalidated->setText(TR("Cur Unvalidated"));
    this->ui->btnCruUnprinted->setText(TR("Cur Unprinted"));
    this->ui->btnCurUnlis->setText(TR("Cur Unlis"));*/
}

void ReViewQueryDlg::Init()
{
    QString today = QDate::currentDate().toString(DATESTYLE);
    this->m_startDateEdit = new CustomDateEdit(false);
    this->m_endDateEdit = new CustomDateEdit(false);
    this->m_startDateEdit->setMaximumSize(180, 32);
    this->m_endDateEdit->setMaximumSize(180, 32);
    this->m_startDateEdit->SetDateTime(today);
    this->m_endDateEdit->SetDateTime(today);

    this->ui->horizontalLayoutDate->addWidget(this->m_startDateEdit);
    this->ui->horizontalLayoutDate->addWidget(new QLabel("-"));
    this->ui->horizontalLayoutDate->addWidget(this->m_endDateEdit);
    this->ui->horizontalLayoutDate->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    connect(this->ui->btnOK,SIGNAL(clicked()),this,SLOT(OnSave()));
    connect(this->ui->btnCancel,SIGNAL(clicked()),this,SLOT(OnCancel()));
}

QString ReViewQueryDlg::GetSampleIDMax()
{
    QString sampleIDMax = this->ui->lineEditSampleID->text().trimmed();
    return sampleIDMax;
}

QString ReViewQueryDlg::GetSampleIDMin()
{
    QString sampleIDMin = this->ui->lineEdit->text().trimmed();
    return sampleIDMin;
}

void ReViewQueryDlg::GenerateQueryCondition()
{
    this->m_query.Clear();
    /*QString sampleIDMin = this->ui->lineEditSampleID->text().trimmed();
    QString sampleIDMax = this->ui->lineEdit->text().trimmed();

    if (!sampleIDMin.isEmpty())
    {
        this->m_query.And("sampleID", ">=", sampleIDMin);
    }

    if (!sampleIDMax.isEmpty())
    {
        this->m_query.And("sampleID", "<=", sampleIDMax);
    }*/

    if (this->m_startDateEdit->isWholeDate())
    {
        this->m_query.And("checkDate", ">=", this->m_startDateEdit->GetDateTime());
    }

    if (this->m_endDateEdit->isWholeDate())
    {
        this->m_query.And("checkDate", "<=", this->m_endDateEdit->GetDateTime());
    }

    this->m_query.And("isFinished", 1);
}

void ReViewQueryDlg::GetBaseQuery()
{
    this->m_query.Clear();
    this->m_query.And("checkDate", QDateTime(QDate::currentDate()));
    this->m_query.And("isFinished", 1);
}

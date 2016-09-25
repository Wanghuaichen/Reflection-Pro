#include "MainBottomCtrlWidget.h"
#include "ui_MainBottomCtrlWidget.h"
#include "EnumMainBottomCtrlType.h"
//#include "StyleManager.h"
//#include "LanguageManager.h"
//#include "ReviewDeleteDlg.h"
//#include "ReViewQueryDlg.h"
//#include "EditResultDlg.h"
//#include "EditInfoDlg.h"

#include <QSignalMapper>
#include <QPushButton>
#include <QDebug>

MainBottomCtrlWidget::MainBottomCtrlWidget(bool review, QWidget *parent) :
    QWidget(parent),
    m_signalMapper(0),
    ui(new Ui::MainBottomCtrlWidget)
{
    ui->setupUi(this);

   // StyleManager::GetInstance()->Init((QWidget*)this);

    this->Init(review);
    this->InitialLanguage();
}

MainBottomCtrlWidget::~MainBottomCtrlWidget()
{
    delete ui;
}

void MainBottomCtrlWidget::SetLockBtnLabel(bool locked)
{
    if (locked)
    {
        this->ui->btnLock->setText(("Unlock"));
    }
    else
    {
        this->ui->btnLock->setText(("Lock"));
    }
}

void MainBottomCtrlWidget::SetQueryLabel(bool hasQuery)
{
    if (hasQuery)
    {
        this->ui->btnQuery->setText(("Cancel search"));
    }
    else
    {
        this->ui->btnQuery->setText(("Search#01"));
    }
}

void MainBottomCtrlWidget::Init(bool review)
{
    this->InitAllButtonsList();
    this->InitButtonGroup(review);

    this->ShowSideButtons(true);

    //
    this->m_signalMapper = new QSignalMapper(this);

    connect(this->ui->btnQuery,        SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnPrevious,     SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnNext,         SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnEditInfo,     SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnCheck,        SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnUnCheck,      SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnEditResult,   SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnPrint,        SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnLIS,          SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnDelete,       SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));
    connect(this->ui->btnLock,         SIGNAL(clicked(bool)), this->m_signalMapper, SLOT(map()));

    this->m_signalMapper->setMapping(this->ui->btnQuery,        (int)MainBotCtrlType::eQuery);
    this->m_signalMapper->setMapping(this->ui->btnPrevious,     (int)MainBotCtrlType::ePreviews);
    this->m_signalMapper->setMapping(this->ui->btnNext,         (int)MainBotCtrlType::eNext);
    this->m_signalMapper->setMapping(this->ui->btnEditInfo,     (int)MainBotCtrlType::eEditInfo);
    this->m_signalMapper->setMapping(this->ui->btnCheck,        (int)MainBotCtrlType::eCheck);
    this->m_signalMapper->setMapping(this->ui->btnUnCheck,      (int)MainBotCtrlType::eUnCheck);
    this->m_signalMapper->setMapping(this->ui->btnEditResult,   (int)MainBotCtrlType::eEditRes);
    this->m_signalMapper->setMapping(this->ui->btnPrint,        (int)MainBotCtrlType::ePrint);
    this->m_signalMapper->setMapping(this->ui->btnLIS,          (int)MainBotCtrlType::eLIS);
    this->m_signalMapper->setMapping(this->ui->btnDelete,       (int)MainBotCtrlType::eDelete);
    this->m_signalMapper->setMapping(this->ui->btnLock,         (int)MainBotCtrlType::eLock);

    connect(this->m_signalMapper, SIGNAL(mapped(int)), this, SIGNAL(ItemButtonClick(int)));
}

void MainBottomCtrlWidget::InitialLanguage()
{
    /*this->ui->btnQuery->setText(TR("Search#01"));
    this->ui->btnPrevious->setText(TR("Former Sample"));
    this->ui->btnNext->setText(TR("Next Sample"));
    this->ui->btnEditInfo->setText(TR("EditInfo"));
    this->ui->btnCheck->setText(TR("Validate"));
    this->ui->btnUnCheck->setText(TR("Undo Validate"));
    this->ui->btnEditResult->setText(TR("EditResult"));
    this->ui->btnPrint->setText(TR("Print"));
    this->ui->btnLIS->setText(TR("Communication#01"));
    this->ui->btnDelete->setText(TR("Delete"));
    this->ui->btnLock->setText(TR("Lock"));*/
}

void MainBottomCtrlWidget::on_btnSwitch_clicked()
{
    this->ShowSideButtons(!this->m_curCtrlGroup.isFrontSide);
}

void MainBottomCtrlWidget::InitAllButtonsList()
{
    this->m_allButtons.push_back(this->ui->btnQuery);
    this->m_allButtons.push_back(this->ui->btnPrevious);
    this->m_allButtons.push_back(this->ui->btnNext);
    this->m_allButtons.push_back(this->ui->btnEditInfo);
    this->m_allButtons.push_back(this->ui->btnCheck);
    this->m_allButtons.push_back(this->ui->btnUnCheck);
    this->m_allButtons.push_back(this->ui->btnEditResult);
    this->m_allButtons.push_back(this->ui->btnPrint);
    this->m_allButtons.push_back(this->ui->btnLIS);
    this->m_allButtons.push_back(this->ui->btnDelete);
    this->m_allButtons.push_back(this->ui->btnLock);
}

void MainBottomCtrlWidget::InitButtonGroup(bool review)
{
    this->m_curCtrlGroup.isFrontSide = true;

    if (review)
    {
        this->m_curCtrlGroup.group = ReviewGroup;

        this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnQuery);
        this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnPrint);
        //this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnLIS);
        //this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnCheck);
        //this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnEditInfo);
        //this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnEditResult);

        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnQuery);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnPrint);
        /*this->m_curCtrlGroup.backSideButtons.append(this->ui->btnLIS);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnCheck);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnUnCheck);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnDelete);*/
    }
    else
    {
        this->m_curCtrlGroup.group = MainGroup;

        this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnPrevious);
        this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnNext);
        this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnPrint);
        this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnLIS);
        this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnEditInfo);
        this->m_curCtrlGroup.frontSideButtons.append(this->ui->btnEditResult);

        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnPrevious);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnNext);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnLock);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnCheck);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnUnCheck);
        this->m_curCtrlGroup.backSideButtons.append(this->ui->btnDelete);
    }
}

void MainBottomCtrlWidget::ShowSideButtons(bool isFront)
{
    this->m_curCtrlGroup.isFrontSide = isFront;

    QList<QPushButton*>* toShowList = 0;
    this->ui->btnSwitch->setText("->");

    if (isFront)
    {
        toShowList = &(this->m_curCtrlGroup.frontSideButtons);
        this->ui->btnSwitch->setText("->");
    }
    else
    {
        toShowList = &(this->m_curCtrlGroup.backSideButtons);
        this->ui->btnSwitch->setText("<-");
    }

    foreach (QPushButton* button, this->m_allButtons)
    {
        bool isToShow = false;
        foreach (QPushButton* toShowButton, *toShowList)
        {
            if (button == toShowButton)
            {
                isToShow = true;
                break;
            }
        }

        if (isToShow)
        {
            button->show();
        }
        else
        {
            button->hide();
        }
    }

}

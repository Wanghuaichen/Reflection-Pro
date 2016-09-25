#include "ReflectionView.h"
#include "EnumViewType.h"
#include "EnumMainBottomCtrlType.h"
#include "ReViewQueryDlg.h"

ReflectionView::ReflectionView(QObject *parent) :
    AbstractView(parent)
{
    this->Initialize();
    this->m_frameWidget = new ReflectionWidget();
    connect(this->m_frameWidget, SIGNAL(BottomItemButtonClick(int)), this, SLOT(BottomItemButtonClicked(int)));
}

ReflectionView::~ReflectionView()
{
}

QWidget *ReflectionView::GetViewsFrame()
{
    return this->m_frameWidget;
}


void ReflectionView::OnSwitchIn()
{
    this->m_frameWidget->OnSwitchIn();
}

void ReflectionView::Initialize()
{
}

void ReflectionView::BottomItemButtonClicked(int itemIdx)
{
    //this->m_editing = true;

    switch(itemIdx)
    {
    case (int)MainBotCtrlType::eQuery:
        this->OnQuery();
        break;
    case (int)MainBotCtrlType::ePrint:
        this->OnPrint();
        break;
    default:
        break;
    }

    //this->m_editing = false;
}

void ReflectionView::OnQuery()
{
    ReViewQueryDlg queryDlg;
    queryDlg.exec();
    QueryCondition condition = queryDlg.GetQuery();
    QString sampleIDMin = queryDlg.GetSampleIDMin();
    QString sampleIDMax = queryDlg.GetSampleIDMax();
    if ((sampleIDMin.isEmpty()) || (sampleIDMax.isEmpty()))
    {
        sampleIDMin = "0";
        sampleIDMax = "999999";
    }

    if (condition.GetConditiaonList().count() > 0)
    {
        this->m_frameWidget->Query(condition, sampleIDMin, sampleIDMax);
    }
}

void ReflectionView::OnPrint()
{
    //this->m_frameWidget->Query(condition, sampleIDMin, sampleIDMax);
}



#include "RootViewController.h"
#include "ReflectionView.h"
#include "AbstractView.h"
#include <QApplication>
#include "ChemistryAnalyser.h"

RootViewController::RootViewController(QObject *parent) :
    QObject(parent)
{
}

RootViewController::~RootViewController()
{
    delete this->m_Analyser;
    qDeleteAll(this->m_viewMap);
    this->m_viewMap.clear();
}

void RootViewController::Initialize()
{
    this->m_Analyser = new ChemistryAnalyser();
    this->Show();
}

void RootViewController::Show()
{
    this->SwitchView(eViewReview);
    this->m_Analyser->show();
}

void RootViewController::SwitchView(eViewType viewType)
{
    AbstractView* pViews = this->GetBottomView(viewType);

    if(0 != pViews)
    {
        //this->m_topView->SwitchTabButton(viewType);
        pViews->OnSwitchIn();

        QWidget* pWidget = pViews->GetViewsFrame();
        if(0 != pWidget)
        {
            this->m_Analyser->SwitchView(pWidget);
            //this->m_curBottomViewType = viewType;
        }
    }
}

AbstractView *RootViewController::GetBottomView(eViewType viewType)
{
    AbstractView* pViews =0;

    if(this->m_viewMap.contains(viewType))
    {
        pViews = this->m_viewMap.value(viewType);
    }
    else
    {
        switch(viewType)
        {
        case eViewReview:
            pViews = new ReflectionView();
            break;
        }

        if(0 != pViews)
        {
            this->m_viewMap.insert(viewType, pViews);
        }
    }

    return pViews;
}

#include "SysTopMenuView.h"
#include "topmenuwidget.h"
//#include "StyleManager.h"
#include <QDebug>

SysTopMenuView::SysTopMenuView(QObject *parent) :
    AbstractView(parent)
{
    this->m_frameWidget = new TopMenuWidget();
    connect(this->m_frameWidget, SIGNAL(ItemClicked(int)), this, SIGNAL(ItemClicked(int)));

    //StyleManager::GetInstance()->SetWidgetBGImage(this->m_frameWidget, "BGFuncBar");
}

SysTopMenuView::~SysTopMenuView()
{
    delete this->m_frameWidget;
}

QWidget* SysTopMenuView::GetViewsFrame()
{
    return this->m_frameWidget;
}

void SysTopMenuView::SwitchTabButton(eViewType viewType)
{
    //this->m_frameWidget->SwitchTabButton(viewType);
}


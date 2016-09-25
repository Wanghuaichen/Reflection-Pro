#include "ChemistryAnalyser.h"
/*#include "FontManager.h"
#include "LanguageManager.h"
#include "UserManager.h"
#include "SoftVersion.h"
#include "StyleManager.h"
#include "ReagentManager.h"
#include "ConfirmMessage.h"
#include "MessageContext.h"
#include "CommonMessage.h"
#include "USystemTrayIconCtrl.h"
*/
#include "filepathmanager.h"
#include <QCloseEvent>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QThread>
#include <QApplication>
#include <QPalette>
//#include "ShowerFlash.h"

ChemistryAnalyser::ChemistryAnalyser(QWidget *parent) :
    QMainWindow(parent),
    m_topWidget(0),
    m_bottomWidget(0),
    m_MainLayout(0),
    m_centerWidget(0),
    m_bUrineAndDryConnect(false)
{
    this->m_centerWidget= new QWidget(this);
    this->setCentralWidget(this->m_centerWidget);
    connect(this, SIGNAL(SigCloseApp()), this, SLOT(ShutDown()));
    //
    this->setMinimumSize(1200, 800);
    this->setMaximumSize(1200, 800);

    this->HideTitle();

    //MessageContext::Instance()->RegistMainWindow(this);
    //connect(ReagentManager::Instance(), SIGNAL(SigShowMainWindow()), this, SLOT(ShowMainWindow()));
    this->ShowMainWindow();
    this->m_MainLayout = new QVBoxLayout(this->m_centerWidget);
    this->m_MainLayout->setContentsMargins(0,0,0,0);
    this->m_MainLayout->setSpacing(0);
    this->m_MainLayout->setContentsMargins(1,1,1,0);
}

ChemistryAnalyser::~ChemistryAnalyser()
{
    delete this->m_MainLayout;
    delete this->m_centerWidget;
}

/*void ChemistryAnalyser::Init(QWidget* topView)
{
    this->m_topWidget = topView;
    this->m_MainLayout = new QVBoxLayout(this->m_centerWidget);
    this->m_MainLayout->addWidget(this->m_topWidget);
    this->m_topWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->m_topWidget->setMaximumHeight(76);
    this->m_topWidget->setMinimumHeight(76);
    this->m_MainLayout->setContentsMargins(0,0,0,0);
    this->m_MainLayout->setSpacing(0);
    this->m_MainLayout->setContentsMargins(1,1,1,0);
    //this->setWindowTitle(SoftVersion().GetAppTitle());
}*/

void ChemistryAnalyser::SwitchView(QWidget* bottomView)
{
    if(0 != bottomView)
    {
        this->SwitchBottomView(bottomView);
    }
}

void ChemistryAnalyser::SwitchBottomView(QWidget* view)
{
    if(0 != view)
    {
        if(0 != this->m_bottomWidget)
        {
            this->m_bottomWidget->hide();
            this->m_MainLayout->removeWidget(this->m_bottomWidget);
        }

        this->m_bottomWidget = view;
        this->m_MainLayout->addWidget(this->m_bottomWidget);
        //this->m_bottomWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        this->m_bottomWidget->show();
    }
}

void ChemistryAnalyser::ShowMainWindow()
{
//    this->hide();
    //  if (!this->isVisible())
    {
       // emit SigShowNormal();
    }

    this->activateWindow();
}

void ChemistryAnalyser::ShutDown()
{
    this->close();
}

void ChemistryAnalyser::SetUrineConnectUAMode(bool isConnect)
{
    this->m_bUrineAndDryConnect = isConnect;
}

void ChemistryAnalyser::ShowHint()
{
    this->show();
    this->raise();
}

void ChemistryAnalyser::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange && (this->windowState() & Qt::WindowMinimized))
    {
        //if (USystemTrayIconCtrl::Connected())
        {
            this->hide();
            this->showNormal();
            QTimer::singleShot(0, this, SIGNAL(SigMinimized()));
        }
    }

    QMainWindow::changeEvent(event);
}

void ChemistryAnalyser::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void ChemistryAnalyser::closeEvent(QCloseEvent *event)
{
    if(this->m_mutex.tryLock(10))
    {
        bool bclose = true;
        if(bclose)
        {
            QMainWindow::closeEvent(event);
        }

        this->m_mutex.unlock();
    }
}

void ChemistryAnalyser::HideTitle()
{
    FilePathManager fpm;
    if (!fpm.CanShowFrameTitle())
    {
        this->setWindowFlags(Qt::FramelessWindowHint);
    }
}

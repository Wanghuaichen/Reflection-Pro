#include <QScrollBar>
#include "QRadioButton"

#include "TouchTableGrid.h"
#include "ui_touchtablegrid.h"
//#include "StyleManager.h"
#include "freezetablewidget.h"

TouchTableGrid::TouchTableGrid(QTableView *tableView, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TouchTableGrid)
{
    ui->setupUi(this);

    this->m_tableView = tableView;
    this->ui->leftLayout->addWidget(this->m_tableView);

    connect(this->ui->btnLineUp,   SIGNAL(clicked(bool)), this, SLOT(OnLineUpClicked()));
    connect(this->ui->btnLineDown,   SIGNAL(clicked(bool)), this, SLOT(OnLineDownClicked()));
    connect(this->ui->btnPageUp,   SIGNAL(clicked(bool)), this, SLOT(OnPageUpClicked()));
    connect(this->ui->btnPageDown,   SIGNAL(clicked(bool)), this, SLOT(OnPageDownClicked()));

    connect(this->ui->btnColumnLeft,   SIGNAL(clicked(bool)), this, SLOT(OnColumnLeftClicked()));
    connect(this->ui->btnColumnRight,   SIGNAL(clicked(bool)), this, SLOT(OnColumnRightClicked()));
    connect(this->ui->btnPageLeft,   SIGNAL(clicked(bool)), this, SLOT(OnPageLeftClicked()));
    connect(this->ui->btnPageRight,   SIGNAL(clicked(bool)), this, SLOT(OnPageRightClicked()));

    this->SetVerWidth(30);
    this->SetHorHeight(30);
    //StyleManager::GetInstance()->Init((QWidget*)this);
    this->ShowHorBar();
    this->ShowVerBar();
}

TouchTableGrid::~TouchTableGrid()
{
    delete ui;
}

QTableView *TouchTableGrid::GetTable()
{
    return this->m_tableView;
}

void TouchTableGrid::SetHorHeight(int height)
{
    this->ui->btnPageLeft->setMinimumHeight(height);
    this->ui->btnPageRight->setMinimumHeight(height);
    this->ui->btnColumnLeft->setMinimumHeight(height);
    this->ui->btnColumnRight->setMinimumHeight(height);
    this->ui->btnPageLeft->setMaximumHeight(height);
    this->ui->btnPageRight->setMaximumHeight(height);
    this->ui->btnColumnLeft->setMaximumHeight(height);
    this->ui->btnColumnRight->setMaximumHeight(height);
}

void TouchTableGrid::SetVerWidth(int width)
{
    this->ui->btnPageUp->setMinimumWidth(width);
    this->ui->btnPageDown->setMinimumWidth(width);
    this->ui->btnLineUp->setMinimumWidth(width);
    this->ui->btnLineDown->setMinimumWidth(width);
    this->ui->btnPageUp->setMaximumWidth(width);
    this->ui->btnPageDown->setMaximumWidth(width);
    this->ui->btnLineUp->setMaximumWidth(width);
    this->ui->btnLineDown->setMaximumWidth(width);
}

void TouchTableGrid::ShowHorBar()
{
#ifdef Q_OS_LINUX
    this->ShowTouchHorBar();
    this->ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
#else
    this->HideTouchHorBar();
    this->m_tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
#endif
}

void TouchTableGrid::HideHorBar()
{
    this->HideTouchHorBar();
    this->m_tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TouchTableGrid::ShowVerBar()
{
#ifdef Q_OS_LINUX
    this->ShowTouchVerBar();
    this->ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
#else
    this->HideTouchVerBar();
    this->m_tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
#endif
}

void TouchTableGrid::HideVerBar()
{
    this->HideTouchVerBar();
    this->m_tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QStandardItemModel* TouchTableGrid::Clear()
{
    QStandardItemModel* model = 0;

    if (this->m_tableView != 0 && this->m_tableView->model() != 0)
    {
        model = (QStandardItemModel*)this->m_tableView->model();
        model->clear();
    }

    return model;
}

void TouchTableGrid::OnLineUpClicked()
{
    QScrollBar* bar = this->m_tableView->verticalScrollBar();
    bar->setSliderPosition(bar->sliderPosition() - 1);
}

void TouchTableGrid::OnLineDownClicked()
{
    QScrollBar* bar = this->m_tableView->verticalScrollBar();
    bar->setSliderPosition(bar->sliderPosition() + 1);
}

void TouchTableGrid::OnPageUpClicked()
{
    QScrollBar* bar = this->m_tableView->verticalScrollBar();
    bar->setSliderPosition(bar->sliderPosition() - bar->pageStep());
}

void TouchTableGrid::OnPageDownClicked()
{
    QScrollBar* bar = this->m_tableView->verticalScrollBar();
    bar->setSliderPosition(bar->sliderPosition() + bar->pageStep());
}

void TouchTableGrid::OnColumnLeftClicked()
{
    QScrollBar* bar = this->m_tableView->horizontalScrollBar();
    bar->setSliderPosition(bar->sliderPosition() - 1);
}

void TouchTableGrid::OnColumnRightClicked()
{
    QScrollBar* bar = this->m_tableView->horizontalScrollBar();
    bar->setSliderPosition(bar->sliderPosition() + 1);
}

void TouchTableGrid::OnPageLeftClicked()
{
    QScrollBar* bar = this->m_tableView->horizontalScrollBar();
    bar->setSliderPosition(bar->sliderPosition() - bar->pageStep());
}

void TouchTableGrid::OnPageRightClicked()
{
    QScrollBar* bar = this->m_tableView->horizontalScrollBar();
    bar->setSliderPosition(bar->sliderPosition() + bar->pageStep());
}

void TouchTableGrid::ShowTouchHorBar()
{
    this->ui->btnPageLeft->show();
    this->ui->btnPageRight->show();
    this->ui->btnColumnLeft->show();
    this->ui->btnColumnRight->show();
}

void TouchTableGrid::HideTouchHorBar()
{
    this->ui->btnPageLeft->hide();
    this->ui->btnPageRight->hide();
    this->ui->btnColumnLeft->hide();
    this->ui->btnColumnRight->hide();
}

void TouchTableGrid::ShowTouchVerBar()
{
    this->ui->btnPageUp->show();
    this->ui->btnPageDown->show();
    this->ui->btnLineUp->show();
    this->ui->btnLineDown->show();
}

void TouchTableGrid::HideTouchVerBar()
{
    this->ui->btnPageUp->hide();
    this->ui->btnPageDown->hide();
    this->ui->btnLineUp->hide();
    this->ui->btnLineDown->hide();
}

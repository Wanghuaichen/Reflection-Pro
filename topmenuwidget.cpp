#include <QMenu>
#include <QAction>

#include "topmenuwidget.h"
#include "ui_topmenuwidget.h"
#include "filepathmanager.h"

TopMenuWidget::TopMenuWidget(QWidget *parent) :
    QWidget(parent),
    m_signalMapper(0),
    m_maintenanceAction(0),
    //m_ptaskManger(taskManger),
    m_timer(0),
    ui(new Ui::TopMenuWidget)
{
    ui->setupUi(this);
}

TopMenuWidget::~TopMenuWidget()
{
    delete ui;
}

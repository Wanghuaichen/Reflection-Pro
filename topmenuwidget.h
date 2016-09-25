#ifndef TOPMENUWIDGET_H
#define TOPMENUWIDGET_H

#include "enumviewtype.h"
#include <QWidget>
#include <QSignalMapper>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include "MenuButton.h"

namespace Ui {
class TopMenuWidget;
}

class TopMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TopMenuWidget(QWidget *parent = 0);
    virtual ~TopMenuWidget();
signals:
private slots:
private:
    Ui::TopMenuWidget *ui;
    QSignalMapper* m_signalMapper;
    QMenu* m_menu;
    QAction* m_maintenanceAction;
    QTimer* m_timer;
};

#endif // TOPMENUWIDGET_H

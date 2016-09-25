#include "MenuButton.h"
#include "filepathmanager.h"

#include <QPaintEvent>
#include <QPainter>

MenuButton::MenuButton(QWidget *parent) :
    QToolButton(parent)
    , m_selected(false)
{
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void MenuButton::SetBackGroundColor(QColor color)
{
    QBrush brush(color);
    QPalette palette;
    palette.setBrush(this->backgroundRole(),brush);
    this->setPalette(palette);
    // this->setMask(pixmap.mask())
    this->setAutoFillBackground(true);
}
bool MenuButton::selected() const
{
    return m_selected;
}

void MenuButton::setSelected(bool selected)
{
    m_selected = selected;

    if (this->m_selected)
    {
        // has back ground image
        this->SetBackGroundColor(QColor(176, 194, 213, 255));
        this->setStyleSheet("QToolButton{border-radius:5px;border-width 1px;}");
    }
    else
    {
        // set transparent
        this->setStyleSheet("QToolButton{border-radius:5px;border-width 1px;background:#cfdae6;}");
    }

    this->update();
}


#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QMouseEvent>
#include <QToolButton>

class QColor;

class MenuButton : public QToolButton
{
    Q_OBJECT
public:
    explicit MenuButton(QWidget *parent = 0);

    bool selected() const;
    void setSelected(bool selected);

private:
    void SetBackGroundColor(QColor color);

    bool m_selected;

};

#endif // MENUBUTTON_H

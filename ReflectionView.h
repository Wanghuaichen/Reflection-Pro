#ifndef REFLECTIONVIEW_H
#define REFLECTIONVIEW_H

#include <QWidget>
#include "ReflectionWidget.h"
#include "AbstractView.h"

class ReflectionView : public AbstractView
{
    Q_OBJECT

public:
    explicit ReflectionView(QObject *parent = 0);
    ~ReflectionView();
    virtual QWidget* GetViewsFrame();

    virtual void OnSwitchIn();

public slots:
    void BottomItemButtonClicked(int itemIdx);

public:
    void Initialize();
    void OnQuery();
    void OnPrint();
private:

private:
    ReflectionWidget* m_frameWidget;

};

#endif // REFLECTIONVIEW_H

#ifndef SYSTOPMENUVIEW_H
#define SYSTOPMENUVIEW_H
#include "AbstractView.h"
#include "enumviewtype.h"
//#include "SampleTaskManager.h"
class TopMenuWidget;

class SysTopMenuView : public AbstractView
{
    Q_OBJECT
public:
    explicit SysTopMenuView(QObject *parent = 0);
    virtual ~SysTopMenuView();
    virtual QWidget* GetViewsFrame();
    void SwitchTabButton(eViewType viewType);

signals:
    void ItemClicked(int viewTypeIdx);
protected slots:

private:
    TopMenuWidget* m_frameWidget;
};

#endif // SYSTOPMENUVIEW_H

#ifndef ROOTVIEWCONTROLLER_H
#define ROOTVIEWCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include "EnumViewType.h"
#include "UWinEventFilter.h"
class QWidget;
class ChemistryAnalyser;
class AbstractView;
class RootViewController : public QObject
{
    Q_OBJECT
public:
    explicit RootViewController(QObject *parent = 0);
    virtual ~RootViewController();
    void Show();
    void Initialize();
public:
    void SwitchView(eViewType viewType);
    QAbstractNativeEventFilter *getWinFilter();
    AbstractView *GetBottomView(eViewType viewType);
    //QWidget *GetTopView();
signals:

public slots:

private:
    QMap<eViewType, AbstractView*> m_viewMap;
    ChemistryAnalyser* m_Analyser;

};

#endif // ROOTVIEWCONTROLLER_H

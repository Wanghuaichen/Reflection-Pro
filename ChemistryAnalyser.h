#ifndef CHEMISTRYANALYSER_H
#define CHEMISTRYANALYSER_H

#include <QMainWindow>
#include <QReadWriteLock>
#include <QMutex>
//#include "RollLabel.h"
//#include "EnumInstrStatus.h"
//#include "MaintainManager.h"
class QGridLayout;
class QVBoxLayout;
class QStatusBar;
class QLabel;
class QTimer;
class ShowerFlash;

class ChemistryAnalyser : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChemistryAnalyser(QWidget *parent = 0);
    virtual ~ChemistryAnalyser();
    //void Init(QWidget* topView);
    void SwitchView(QWidget* bottomView);
    void SwitchBottomView(QWidget* view);

signals:
    void SigMinimized();
    void SigShowNormal();
    void SigCloseApp(bool isMaintain);
public slots:
    void ShowMainWindow();
    void ShutDown();
    void SetUrineConnectUAMode(bool isConnect);
    void ShowHint();
protected slots:

protected:
    virtual void changeEvent(QEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    void HideTitle();
private:
    QWidget* m_centerWidget;
    QWidget* m_topWidget;
    QWidget* m_bottomWidget;
    QVBoxLayout* m_MainLayout;
    QReadWriteLock m_locker;
    bool m_bUrineAndDryConnect;
    QMutex  m_mutex;
};

#endif // CHEMISTRYANALYSER_H

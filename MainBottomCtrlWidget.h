#ifndef MAINBOTTOMCTRLWIDGET_H
#define MAINBOTTOMCTRLWIDGET_H

#include <QWidget>
#include <QList>

class QPushButton;

namespace Ui {
class MainBottomCtrlWidget;
}

class QSignalMapper;

class MainBottomCtrlWidget : public QWidget
{
    Q_OBJECT
private:
    enum GroupType
    {
        MainGroup,
        ReviewGroup,
    };

    struct CtrlButtonGroup
    {
        GroupType group;
        bool isFrontSide;
        QList<QPushButton*> frontSideButtons;
        QList<QPushButton*> backSideButtons;
    };

public:
    explicit MainBottomCtrlWidget(bool Review, QWidget *parent = 0);
    virtual ~MainBottomCtrlWidget();

    void SetLockBtnLabel(bool locked);
    void SetQueryLabel(bool hasQuery);

signals:
    void ItemButtonClick(int itemIdx);

protected:
    void Init(bool Review);
    void InitialLanguage();

private slots:
    void on_btnSwitch_clicked();

private:
    void InitAllButtonsList();
    void InitButtonGroup(bool review);
    void HideAllButtons();
    void ShowSideButtons(bool isFront);

    Ui::MainBottomCtrlWidget *ui;
    QSignalMapper* m_signalMapper;
    CtrlButtonGroup m_curCtrlGroup;
    QList<QPushButton*> m_allButtons;
};

#endif // MAINBOTTOMCTRLWIDGET_H

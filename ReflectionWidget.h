#ifndef REFLECTIONWIDGET_H
#define REFLECTIONWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QList>
#include <QLabel>
#include "ReflectionInfo.h"
#include "QueryCondition.h"
#include "TouchTableGrid.h"
#include "freezetablewidget.h"
#include "ParameterSystem.h"
#include "UIWidthManager.h"
#include "MainBottomCtrlWidget.h"
#include "RecordInfo.h"
#include "ReflectedChecker.h"
namespace Ui {
class ReflectionWidget;
}

class ReflectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReflectionWidget(QWidget *parent = 0);
    ~ReflectionWidget();

signals:
    void BottomItemButtonClick(int itemIdx);

public:
    void OnSwitchIn();
    void RefreshRecords();
    void RefreshOnlyItems();
    void LoadRecords(QueryCondition query);
    void ClearCtrl();
    QStringList GetHeaders();
    void InitCtrl();
    void LoadRecord(QStandardItemModel *model, int rowIndex, ReflectionInfo &reflection, RecordInfo &record);
    void SetColumnWidth(FreezeTableWidget *table, QStandardItemModel *model);
    void InitRecordIndex(int row);
    void Query(QueryCondition query, QString sampleIDMin, QString sampleIDMax);
    QList<RecordInfo> GetRecordInfoList(QueryCondition query);
    int GetItemCount(RecordInfo record);
    bool SetBackgroundColor(EnumItemCount itemCount, int column);
private:
    QDateTime m_firstReviewDate;
    bool m_hasQuery;
    MainBottomCtrlWidget* m_bottomWidget;
    TouchTableGrid* m_topTouchTableGrid;
    QueryCondition  m_queryCondition;
    ReflectedChecker m_ReflectChecker;
    long m_recordIndex;
    QLabel* m_label;

    Ui::ReflectionWidget *ui;
};

#endif // REFLECTIONWIDGET_H

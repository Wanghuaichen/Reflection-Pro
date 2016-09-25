#include "ReflectionWidget.h"
#include "ui_ReflectionWidget.h"
#include "PatientSystem.h"
#include <QDebug>
#include "WaitDialog.h"
ReflectionWidget::ReflectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReflectionWidget)
{
    ui->setupUi(this);
    this->m_bottomWidget = new MainBottomCtrlWidget(true, this);
    connect(this->m_bottomWidget, SIGNAL(ItemButtonClick(int)), this, SIGNAL(BottomItemButtonClick(int)));

    this->m_firstReviewDate.setDate(QDateTime::currentDateTime().date());
}

ReflectionWidget::~ReflectionWidget()
{
    delete ui;
}

void ReflectionWidget::OnSwitchIn()
{
    if (this->m_hasQuery)
    {
        // check deleted items in list and refresh every item.
        //this->RefreshOnlyItems();
        this->RefreshRecords();
    }
    else
    {
        this->RefreshRecords();
    }
}

void ReflectionWidget::RefreshRecords()
{
    /*WaitingMessage message(TR("Waiting"), TR("Waiting"));
    message.CloseWaitMessage();*/
    QueryCondition query("checkDate", ">=", this->m_firstReviewDate);
    this->LoadRecords(query);

}

void ReflectionWidget::RefreshOnlyItems()
{

}

void ReflectionWidget::LoadRecords(QueryCondition query)
{
    //this->ClearCtrl();
    this->m_queryCondition = query;
    query.And("isFinished", 1);
    QList<ReflectionInfo> reflectionList = PatientSystem::Instance()->GetReflectionsByCondition(query, 0 , 99999999);
    QList<RecordInfo> recordList =  this->GetRecordInfoList(query);
    QStringList headList = this->GetHeaders();
    QStandardItemModel *model = new QStandardItemModel(reflectionList.count(), headList.count());
    model->setHorizontalHeaderLabels(headList);

    for(int i = 0; i < reflectionList.count(); i++)
    {
        ReflectionInfo reflection = reflectionList[i];
        RecordInfo record = recordList[i];
        this->LoadRecord(model, i, reflection, record);
    }

    FreezeTableWidget *table = new FreezeTableWidget(model);

    table->ResizeHeader();
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    //table->setColumnHidden(eColumnRecordIndex, true);
    table->setSortingEnabled(false);
    table->setWordWrap(false);
    table->setAlternatingRowColors(true);
    table->setEditTriggers(QTableWidget::NoEditTriggers);
    table->verticalHeader()->hide();
    this->SetColumnWidth(table, model);
    //connect(model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(RowIndexChanged()));
    //connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(RowIndexChanged()));

    this->m_topTouchTableGrid = new TouchTableGrid(table, this);
    this->m_topTouchTableGrid->SetHorHeight(50);
    this->m_topTouchTableGrid->SetVerWidth(30);

    if (recordList.count() > 0)
    {
        this->InitRecordIndex(recordList.length() - 1);
    }

    this->InitCtrl();
}

void ReflectionWidget::ClearCtrl()
{
    delete this->m_topTouchTableGrid;
    this->m_topTouchTableGrid = 0;
     this->m_recordIndex = -1;
}

QStringList ReflectionWidget::GetHeaders()
{
    QStringList headers;
    headers.append(("SampleID"));
    //headers.append(("ReflectionIndex"));
    headers.append(("TestDate"));
    headers.append(("TestTime"));
    headers.append(("itemCount"));
    headers.append(("LEU"));
    headers.append(("URO"));
    headers.append(("MCA"));
    headers.append(("PRO"));
    headers.append(("BIL"));
    headers.append(("GLU"));
    headers.append(("VitC"));
    headers.append(("SG"));
    headers.append(("KET"));
    headers.append(("NIT"));
    headers.append(("CRE"));
    headers.append(("pH"));
    headers.append(("BLD"));
    headers.append(("CA"));
    headers.append(("Color"));
    headers.append(("Turb"));

    return headers;
}

void ReflectionWidget::InitCtrl()
{
    this->ui->gridLayout->addWidget(this->m_topTouchTableGrid,0,0,1,2);
    this->ui->gridLayout->addWidget(this->m_bottomWidget,1,0,1,2);
    this->m_topTouchTableGrid->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->m_bottomWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    this->ui->gridLayout->setMargin(1);
}

void ReflectionWidget::LoadRecord(QStandardItemModel *model, int rowIndex, ReflectionInfo &reflection, RecordInfo &record)
{
    QList<EnumChemistryType> sortList = ParameterSystem::Instance()->GetParamSortList();
    Qt::Alignment alignment = Qt::AlignCenter;

    int column = 4;
    bool isRowIndexRed = false;
    QString strValue = "";
    foreach(EnumChemistryType type, sortList)
    {
        QString value = "";

        QList<ReflectionItem> list = reflection.ValueList();
        foreach(ReflectionItem item, list)
        {
            if (item.Type() == type)
            {
                value = item.Value();
                //qDebug() << value << " ";
                break;
            }
        }

        value.remove("mg/L");
        value.remove("mmol/L");

        if (value.isEmpty())
        {
            EnumItemCount itemCount = record.GetItemCount();
            isRowIndexRed |= this->SetBackgroundColor(itemCount, column);
        }

        QString color = "black";//record.GetResult()->IsItemAlert(type) ? "red" : "black";
        ReflectedChecker::ReflectState ret = this->m_ReflectChecker.CalcCheckReflection(list);
        switch (ret) {
        case ReflectedChecker::ReflectState::ReflectLowOVER:
            color = "blue";
            isRowIndexRed = true;
            break;
        case ReflectedChecker::ReflectState::ReflectUpOVER:
            color = "red";
            isRowIndexRed = true;
            break;
        default:
            break;
        }

        TableCell::SetViewValue(model, rowIndex, column++, value, Qt::AlignRight, color);

        strValue += value;
    }

    int itemCount = this->GetItemCount(record);

    TableCell::SetViewValue(model, rowIndex, 0,     record.SampleID(), alignment);
    TableCell::SetViewValue(model, rowIndex, 1,     record.CheckDate().toString("yyyy-MM-dd"), alignment);
    TableCell::SetViewValue(model, rowIndex, 2,     record.CheckTime().toString(), alignment);
    TableCell::SetViewValue(model, rowIndex, 3,     QString::number(itemCount), alignment);

    if (isRowIndexRed)
    {
        QStandardItem* item = model->item(rowIndex, 0);//eColumnSampleID);
        if(0 != item)
        {
            item->setBackground(QBrush(QColor(Qt::red)));
        }
    }
}

void ReflectionWidget::SetColumnWidth(FreezeTableWidget* table, QStandardItemModel* model)
{
    QList<int> widths = UIWidthManager::GetInstance()->GetWidthOfTable("ReviewWidget");

    for (int i = 0; i < model->columnCount(); i++)
    {
        if (i < 4)
        {
            table->setColumnWidth(i, 100);
        }

        if (i < widths.length())
        {
            table->setColumnWidth(i, 150);
        }
    }
}

void ReflectionWidget::InitRecordIndex(int row)
{
    QTableView* pTable = this->m_topTouchTableGrid->GetTable();
    pTable->selectRow(row);
    pTable->scrollToBottom();

    QStandardItemModel* model = (QStandardItemModel*)(pTable->model());
    QStandardItem *item = model->item(row, 1);//eColumnRecordIndex);

    //this->m_recordIndex = item->text().toLong();
}

void ReflectionWidget::Query(QueryCondition query, QString sampleIDMin, QString sampleIDMax)
{
    //this->SetQueryLabel(true);

    QStandardItemModel* model = (QStandardItemModel*)this->m_topTouchTableGrid->GetTable()->model();
    model->removeRows(0, model->rowCount());

    this->m_queryCondition = query;
    QList<ReflectionInfo> reflectionList = PatientSystem::Instance()->GetReflectionsByCondition(query, sampleIDMin.toLong(), sampleIDMax.toLong());

    //ProgressMessage progress(TR("Waiting"), recordList.length());
    //WaitDialog waitDialog;
    //waitDialog.exec();
    QList<RecordInfo> recordList =  this->GetRecordInfoList(query);

    for(int i = 0; i < reflectionList.count(); i++)
    {
        ReflectionInfo reflection = reflectionList[i];
        model->insertRow(i);
        RecordInfo record = recordList[i];
        this->LoadRecord(model, i, reflection, record);
        //progress.Step(1);
    }

    if (reflectionList.count() > 0)
    {
        this->InitRecordIndex(0);
    }

    //waitDialog.close();
    //progress.CloseMessage();
}

QList<RecordInfo> ReflectionWidget::GetRecordInfoList(QueryCondition query)
{
    QList<RecordInfo> recordInfoList = PatientSystem::Instance()->GetRecordWithReflection(query);
    return recordInfoList;
}

int ReflectionWidget::GetItemCount(RecordInfo record)
{
    int itemCount = 0;
    if (record.GetItemCount() == 0)
    {
        itemCount = 11;
    }
    else if (record.GetItemCount() == 1)
    {
        itemCount = 12;
    }
    else if (record.GetItemCount() == 2)
    {
        itemCount = 14;
    }

    return itemCount;
}

bool ReflectionWidget::SetBackgroundColor(EnumItemCount itemCount, int column)
{
    bool isRowIndexRed = false;
    switch (itemCount)
    {
        case e11Items:
            if (column == 4+2 || column == 12+2 || column == 15+2 || column == 17+2)
            {
                isRowIndexRed = false;
            }
            else
            {
                isRowIndexRed = true;
            }
            break;
        case e12Items:
            if (column == 12+2 ||column == 15+2 || column == 17+2)
            {
                isRowIndexRed = false;
            }
            else
            {
                isRowIndexRed = true;
            }
            break;
        case e14Items:
        if (column == 17+2)
        {
            isRowIndexRed = false;
        }
        else
        {
            isRowIndexRed = true;
        }
            break;
        default:
            isRowIndexRed = false;
            break;
     }

    return isRowIndexRed;
}

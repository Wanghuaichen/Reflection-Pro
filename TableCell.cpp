#include "TableCell.h"
#include <QRadioButton>
#include <QDebug>

TableCell::TableCell()
{
}

TableCell::~TableCell()
{
}

void TableCell::SetWidgetValue(QTableWidget *table, int row, int column, QString value, int alignment)
{
    QTableWidgetItem* item = new QTableWidgetItem(value);
    item->setTextAlignment(alignment);
    table->setItem(row, column, item);
}

void TableCell::SetWidgetWidget(QTableWidget *table, int row, int column, QWidget *widget)
{
    table->setCellWidget(row, column, widget);
}

void TableCell::SetWidgetRbtn(QTableWidget *table, int row, int column, bool isChecked)
{
    QRadioButton *rbtn = new QRadioButton();
    rbtn->setChecked(isChecked);
    table->setCellWidget(row, column, rbtn);
}

void TableCell::SetViewValue(QStandardItemModel *model, int row, int column, QString value, Qt::Alignment alignment, QString color)
{
    QStandardItem* item = model->item(row, column);
    if (0== item)
    {
        item = new QStandardItem(value);
    }
    /*else if (1 == item->column())
    {
        item = new QStandardItem(value);
    }
    else if (2 == item->column())
    {
        item = new QStandardItem(value);
    }
    else if (3 == item->column())
    {
        item = new QStandardItem(value);
    }*/
    else
    {
        item->setText(value);
    }

    item->setTextAlignment(alignment);
    item->setForeground(QBrush(QColor(color)));
    model->setItem(row, column, item);
}

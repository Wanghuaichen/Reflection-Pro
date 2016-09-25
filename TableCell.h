#ifndef TABLECELL_H
#define TABLECELL_H

#include <QTableWidget>
#include <QString>
#include <QStandardItem>

class TableCell
{
public:
    TableCell();
    virtual ~TableCell();

    static void SetWidgetValue(QTableWidget* table, int row, int column, QString value, int alignment = Qt::AlignLeft);
    static void SetWidgetWidget(QTableWidget* table, int row, int column, QWidget* widget);
    static void SetWidgetRbtn(QTableWidget* table, int row, int column, bool isChecked);

    static void SetViewValue(QStandardItemModel* model, int row, int column, QString value, Qt::Alignment alignment = Qt::AlignLeft, QString color = "black");

};

#endif // TABLECELL_H

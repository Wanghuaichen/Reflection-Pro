#ifndef TOUCHTABLEGRID_H
#define TOUCHTABLEGRID_H

#include <QWidget>
#include <QTableWidget>
#include <QStandardItemModel>
#include "TableCell.h"

namespace Ui {
class TouchTableGrid;
}

class TouchTableGrid : public QWidget
{
    Q_OBJECT

public:
    explicit TouchTableGrid(QTableView *tableView, QWidget *parent = 0);
    virtual ~TouchTableGrid();

    QTableView *GetTable();
    void SetHorHeight(int height);
    void SetVerWidth(int width);

    void ShowHorBar();
    void HideHorBar();

    void ShowVerBar();
    void HideVerBar();

    QStandardItemModel *Clear();

protected slots:
    void OnLineUpClicked();
    void OnLineDownClicked();
    void OnPageUpClicked();
    void OnPageDownClicked();
    void OnColumnLeftClicked();
    void OnColumnRightClicked();
    void OnPageLeftClicked();
    void OnPageRightClicked();

private:
    void ShowTouchHorBar();
    void HideTouchHorBar();
    void ShowTouchVerBar();
    void HideTouchVerBar();

    Ui::TouchTableGrid *ui;
    QTableView *m_tableView;
};

#endif // TOUCHTABLEGRID_H

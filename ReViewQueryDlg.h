#ifndef REVIEWQUERYDLG_H
#define REVIEWQUERYDLG_H

#include <QDialog>
#include "QueryCondition.h"
#include "CustomDateEdit.h"

namespace Ui {
class ReViewQueryDlg;
}

class ReViewQueryDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ReViewQueryDlg(QWidget *parent = 0);
    virtual ~ReViewQueryDlg();
    QueryCondition GetQuery() const;

    QString GetSampleIDMin();
    QString GetSampleIDMax();
protected slots:
    void OnSave();
    void OnCancel();

private:
    Ui::ReViewQueryDlg *ui;
    CustomDateEdit* m_startDateEdit;
    CustomDateEdit* m_endDateEdit;
    QueryCondition m_query;

    void InitLanguage();
    void Init();
    void GenerateQueryCondition();
    void GetBaseQuery();
};

#endif // REVIEWQUERYDLG_H

#ifndef RECORDACCESS_H
#define RECORDACCESS_H

#include "IDataAccess.h"
#include "FieldDefine.h"
#include "RecordInfoSaver.h"

#include <QList>
#include <QSqlRecord>

class RecordAccess : IDataAccess
{
public:
    RecordAccess();
    virtual ~RecordAccess();
    virtual TableDefine GetTableDefine();

    QList<FieldData> GetData(RecordInfo record);
    RecordInfo ProcessSqlrecord(QSqlRecord sqlRecord);
private:
    RecordInfoSaver recordInfoSaver;
};

#endif // RECORDACCESS_H

#ifndef RECORDWITHREFLECTIONDATAACCESS_H
#define RECORDWITHREFLECTIONDATAACCESS_H
#include "IDataAccess.h"
#include "RecordInfo.h"
#include "ReflectionInfo.h"
#include "FieldDefine.h"
#include "ReflectionInfo.h"
#include "RecordInfoSaver.h"
#include <QSqlRecord>

struct RecordWithReflection
{
    RecordInfo     record;
    ReflectionInfo reflection;
};

class RecordWithReflectionDataAccess : public IDataAccess
{
public:
    RecordWithReflectionDataAccess();
    virtual ~RecordWithReflectionDataAccess();

    virtual TableDefine GetTableDefine();
    QList<FieldData> GetData(RecordInfo record);
    RecordWithReflection ProcessSqlrecord(QSqlRecord record);
};

#endif // RECORDWITHREFLECTIONDATAACCESS_H

#ifndef REFLECTIONACCESS_H
#define REFLECTIONACCESS_H
#include "IDataAccess.h"
#include "ReflectionInfoSaver.h"
#include <QList>
#include <QSqlRecord>

class ReflectionAccess : public IDataAccess
{
public:
    ReflectionAccess();
    virtual ~ReflectionAccess();

    virtual TableDefine GetTableDefine();
    QList<FieldData> GetData(ReflectionInfo reflection);
    ReflectionInfo ProcessSqlrecord(QSqlRecord sqlRecord, int index = 0);

private:
    ReflectionInfoSaver reflectionInfoSaver;
};

#endif // REFLECTIONACCESS_H

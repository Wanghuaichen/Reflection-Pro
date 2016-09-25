#ifndef PATIENTSYSTEM_H
#define PATIENTSYSTEM_H
#include <QList>
#include "QueryCondition.h"
#include "DBManager.h"
#include "ReflectionInfo.h"
#include "RecordInfo.h"

class PatientSystem : public DBManager
{
public:
    static PatientSystem* Instance();
    virtual ~PatientSystem();
    QList<RecordInfo> GetRecordWithReflection(QueryCondition queryCondition);
    QList<ReflectionInfo> GetReflectionsByCondition(QueryCondition queryCondition, long sampleIdFrom, long sampleIdTo);
    QList<QSqlRecord> OnGetReflectionByCondtion(QueryCondition condition);
private:
    PatientSystem();

};

#endif // PATIENTSYSTEM_H

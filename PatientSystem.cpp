#include "PatientSystem.h"
#include "RecordWithReflectionDataAccess.h"


PatientSystem::PatientSystem()
{
    if (this->InitialDatabase(PATIENTDATAFILENAME))
    {
    }

    //InitDbaccessUpgrade initDbaccessUpgrade;
    //initDbaccessUpgrade.DbaccessUpgrade(&this->m_dbaccess);

    //this->DeleteUnnecessaryFile();
}

PatientSystem::~PatientSystem()
{
}

PatientSystem* PatientSystem::Instance()
{
    static PatientSystem instance;
    return &instance;
}

QList<RecordInfo> PatientSystem::GetRecordWithReflection(QueryCondition queryCondition)
{
    QList<RecordInfo> recordList;
    QList<QSqlRecord> sqlrecords = this->OnGetReflectionByCondtion(queryCondition);
    RecordWithReflectionDataAccess dataAccess;
    foreach (QSqlRecord record, sqlrecords)
    {
        RecordWithReflection info = dataAccess.ProcessSqlrecord(record);
        info.record.SetReflection(info.reflection);
        recordList.append(info.record);
    }

    return recordList;
}


QList<ReflectionInfo> PatientSystem::GetReflectionsByCondition(QueryCondition queryCondition, long sampleIdFrom, long sampleIdTo)
{
    QList<ReflectionInfo> list;
    QList<RecordInfo> recordList = this->GetRecordWithReflection(queryCondition);
    bool ret = false;
    foreach(RecordInfo record, recordList)
    {
        long sampeld = record.SampleID().toLong(&ret);
        if(ret)
        {
            if((sampeld >= sampleIdFrom) && (sampeld <= sampleIdTo))
            {
                ReflectionInfo info = *record.GetReflection();
                list.append(info);
            }
        }
    }

    return list;
}

QList<QSqlRecord> PatientSystem::OnGetReflectionByCondtion(QueryCondition condition)
{
    QMutexLocker locker(&this->m_mutex);

    RecordWithReflectionDataAccess dataAccess;

    QList<QSqlRecord> sqlrecords = this->m_dbaccess.GetRecordsByCondition(dataAccess.GetTableDefine(), condition);

    return sqlrecords;
}

#include "RecordWithReflectionDataAccess.h"
#include "ReflectionAccess.h"
#include "ReflectionInfoSaver.h"
#include "RecordAccess.h"

RecordWithReflectionDataAccess::RecordWithReflectionDataAccess()
{
}

RecordWithReflectionDataAccess::~RecordWithReflectionDataAccess()
{

}

TableDefine RecordWithReflectionDataAccess::GetTableDefine()
{
    TableDefine recordInnerJoinResultTable;

    RecordInfoSaver recordInfoSaver;
    recordInnerJoinResultTable.Fields.append(recordInfoSaver.table.Fields);

    ReflectionInfoSaver reflectInfoSaver;
    recordInnerJoinResultTable.Fields.append(reflectInfoSaver.table.Fields);

    recordInnerJoinResultTable.TableName = recordInfoSaver.table.TableName
            + " inner join "
            + reflectInfoSaver.table.TableName
            + " on "
            + recordInfoSaver.table.TableName + ".curReflectionIndex = "
            + reflectInfoSaver.table.TableName + ".ReflectionIndex";

    return recordInnerJoinResultTable;
}

QList<FieldData> RecordWithReflectionDataAccess::GetData(RecordInfo record)
{
    QList<FieldData> list;
    return list;
}

RecordWithReflection RecordWithReflectionDataAccess::ProcessSqlrecord(QSqlRecord record)
{
    RecordWithReflection recordWithReflection;

    RecordAccess recordAccess;
    recordWithReflection.record = recordAccess.ProcessSqlrecord(record);

    RecordInfoSaver recordInfoSaver;
    ReflectionAccess reflectAccess;
    recordWithReflection.reflection = reflectAccess.ProcessSqlrecord(record, recordInfoSaver.table.Fields.length());

    return recordWithReflection;
}

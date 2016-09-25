#include "ReflectionAccess.h"

ReflectionAccess::ReflectionAccess()
{
}

ReflectionAccess::~ReflectionAccess()
{
}

TableDefine ReflectionAccess::GetTableDefine()
{
    return this->reflectionInfoSaver.table;
}

QList<FieldData> ReflectionAccess::GetData(ReflectionInfo reflection)
{
    return this->reflectionInfoSaver.GetData(reflection);
}

ReflectionInfo ReflectionAccess::ProcessSqlrecord(QSqlRecord sqlRecord, int index)
{
    ReflectionInfo reflection;
    reflection.SetReflectIndex(sqlRecord.value(index++).toLongLong());

    for(int i = LEU; i <= Turbidity; i++)
    {
        QString valueString = sqlRecord.value(index++).toString();
        reflection.SetValue((EnumChemistryType)i, valueString);
    }

    return reflection;
}


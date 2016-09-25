#include "InfoSaver.h"
#include "FieldDefine.h"

InfoSaver::InfoSaver()
{
}

InfoSaver::~InfoSaver()
{
}

FieldDefine InfoSaver::GetFieldDefine(QString name, QString type)
{
    FieldDefine fieldDefine(name, type);
    return fieldDefine;
}

FieldData InfoSaver::MakeMap(QString fieldName, QVariant fieldValue)
{
    FieldDefine fieldDefine;

    foreach (FieldDefine eachField, this->table.Fields)
    {
        if (fieldName == eachField.name)
        {
            fieldDefine = eachField;
            break;
        }
    }

    // fieldDefine.name = this->table.TableName + "." + fieldDefine.name;

    FieldData fieldData;
    fieldData.Field = fieldDefine;
    fieldData.Value = fieldValue;

    return fieldData;
}

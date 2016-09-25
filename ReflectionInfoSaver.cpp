#include "ReflectionInfoSaver.h"
#include "ParameterSystem.h"
#include "ChemistryType.h"

ReflectionInfoSaver::ReflectionInfoSaver()
    : InfoSaver()
{
    this->table.TableName = "reflection";

    this->table.Fields << this->GetFieldDefine("ReflectionIndex", "integer primary key");

    for (int i = LEU; i <= Turbidity; i++)
    {
        this->table.Fields << this->GetFieldDefine(ChemistryType::GetTypeName((EnumChemistryType)i), "varchar(32)");
    }
}

ReflectionInfoSaver::~ReflectionInfoSaver()
{
}

QList<FieldData> ReflectionInfoSaver::GetData(ReflectionInfo reflection)
{
    QList<FieldData> reflectionList;
    ParameterSystem* pParamSystem = ParameterSystem::Instance();
    QList<ReflectionItem> itemList = reflection.ValueList();
    for (QList<ReflectionItem>::iterator itea = itemList.begin(); itea < itemList.end(); ++itea)
    {
        reflectionList << this->MakeMap(pParamSystem->GetKeyNameByType(itea->Type()), itea->Value());
    }

    return reflectionList;
}

#include <QString>

#include "ChemistryType.h"
#include "EnumChemistryType.h"
#include "ParameterSystem.h"

ChemistryType::ChemistryType()
{
}

ChemistryType::~ChemistryType()
{
}

QString ChemistryType::GetTypeName(EnumChemistryType eType)
{
    return ParameterSystem::Instance()->GetKeyNameByType(eType);
}

EnumChemistryType ChemistryType::GetEnumType(QString name)
{
    return ParameterSystem::Instance()->GetTypeByKeyName(name);
}

QString ChemistryType::GetShowName(EnumChemistryType eType)
{
    return ParameterSystem::Instance()->GetShowNameByType(eType);
}


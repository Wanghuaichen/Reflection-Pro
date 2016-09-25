#include "ReflectionInfo.h"
//#include "DryColorInfo.h"

ReflectionInfo::ReflectionInfo()
{
    this->Init();
}

ReflectionInfo::~ReflectionInfo()
{

}

long ReflectionInfo::GetReflectIndex() const
{
    return this->m_reflectIndex;
}

void ReflectionInfo::SetReflectIndex(long index)
{
    this->m_reflectIndex = index;
}

QString ReflectionInfo::GetValue(EnumChemistryType type)
{
    QString strValue = "";
    if(this->m_valueMap.contains(type))
    {
        ReflectionItem item = this->m_valueMap.value(type);
        strValue = item.Value();
    }

    return strValue;
}

QList<ReflectionItem> ReflectionInfo::ValueList() const
{
    QList<ReflectionItem> list;
    QMap<EnumChemistryType, ReflectionItem>::const_iterator itea;
    for(itea = this->m_valueMap.begin(); itea != m_valueMap.end(); ++itea)
    {
        list.append(itea.value());
    }

    return list;
}

void ReflectionInfo::SetValue(EnumChemistryType item, QString value)
{
    if (this->m_valueMap.contains(item))
    {
        this->m_valueMap[item].SetValue(value);
    }
}

void ReflectionInfo::SetValue(const DryReflectedSt *dryReflected, QMap<EnumChemistryType, int> itemIndexMap)
{
    /*QMap<EnumChemistryType, int>::iterator its;
    for(its = itemIndexMap.begin(); its != itemIndexMap.end(); ++its)
    {
        EnumChemistryType type = its.key();
        int index = its.value();
        QString value = dryReflected->ColorArray[index].ToSmallString();
        this->SetValue(type, value);
    }*/
}

void ReflectionInfo::Init()
{
    this->m_reflectIndex = -1;

    for (int i = LEU; i <= Turbidity; i++)
    {
        EnumChemistryType type = (EnumChemistryType)i;
        ReflectionItem valueItem(type);
        this->m_valueMap.insert(type, valueItem);
        this->m_typeList.append(type);
    }
}


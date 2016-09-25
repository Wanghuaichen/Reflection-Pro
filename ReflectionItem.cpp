#include "ReflectionItem.h"

ReflectionItem::ReflectionItem(EnumChemistryType type, QString value):
    m_type(type),
    m_value(value)
{
}

ReflectionItem::ReflectionItem(EnumChemistryType type):
    m_type(type),
    m_value("")
{
}

ReflectionItem::ReflectionItem():
    m_type(LEU),
    m_value("")
{
}

ReflectionItem::~ReflectionItem()
{
}

void ReflectionItem::SetValue(QString value)
{
    this->m_value = value;
}

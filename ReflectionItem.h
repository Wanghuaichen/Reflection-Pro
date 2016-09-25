#ifndef REFLECTIONITEM_H
#define REFLECTIONITEM_H
#include "EnumChemistryType.h"
#include <QString>

class ReflectionItem
{
public:
    ReflectionItem(EnumChemistryType type, QString value);
    ReflectionItem(EnumChemistryType type);
    ReflectionItem();
    virtual ~ReflectionItem();
    void SetValue(QString value);
    EnumChemistryType Type() { return this->m_type; }
    QString Value() { return this->m_value; }

private:
    EnumChemistryType m_type;
    QString m_value;
};

#endif // REFLECTIONITEM_H

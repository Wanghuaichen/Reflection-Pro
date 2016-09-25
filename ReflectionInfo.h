#ifndef REFLECTIONINFO_H
#define REFLECTIONINFO_H
#include "EnumChemistryType.h"
#include "ReflectionItem.h"
#include <QString>
#include <QMap>
struct DryReflectedSt;

class ReflectionInfo
{
public:
    ReflectionInfo();
    virtual ~ReflectionInfo();
    long GetReflectIndex() const;
    void SetReflectIndex(long index);
    QString GetValue(EnumChemistryType type);
    QList<ReflectionItem> ValueList() const;
    void SetValue(EnumChemistryType item, QString value);
    void SetValue(const DryReflectedSt *dryReflected, QMap<EnumChemistryType, int> itemIndexMap);

protected:
    void Init();
private:
    long m_reflectIndex;
    QMap<EnumChemistryType, ReflectionItem> m_valueMap;
    QList<EnumChemistryType>                m_typeList;
};

#endif // REFLECTIONINFO_H

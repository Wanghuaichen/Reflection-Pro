#ifndef CHEMISTRYTYPE_H
#define CHEMISTRYTYPE_H

#include <QString>
#include "EnumChemistryType.h"

class ChemistryType
{
public:
    ChemistryType();
    virtual ~ChemistryType();
    static QString GetTypeName(EnumChemistryType eType);
    static EnumChemistryType GetEnumType(QString name);
    static QString GetShowName(EnumChemistryType eType);
};

#endif // CHEMISTRYTYPE_H

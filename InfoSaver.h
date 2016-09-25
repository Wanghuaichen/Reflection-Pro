#ifndef INFOSAVER_H
#define INFOSAVER_H

#include "FieldDefine.h"

#include <QObject>

class InfoSaver
{
public:
    InfoSaver();
    virtual ~InfoSaver();

    TableDefine table;

    FieldDefine GetFieldDefine(QString name, QString type);
    FieldData MakeMap(QString fieldName, QVariant fieldValue);
};

#endif // INFOSAVER_H

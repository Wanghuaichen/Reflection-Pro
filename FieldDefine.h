#ifndef FIELDDEFINE_H
#define FIELDDEFINE_H

#include <QString>
#include <QList>
#include <QObject>
#include <QVariant>

class FieldDefine
{
public:
    QString name;
    QString type;
    bool isKey;

    FieldDefine();
    FieldDefine(QString name, QString type);
    FieldDefine(QString name, QString type, bool isKey);
};

struct FieldData
{
    FieldDefine Field;
    QVariant Value;
};

struct TableDefine
{
    QString TableName;
    QList<FieldDefine> Fields;
};

#endif // FIELDDEFINE_H

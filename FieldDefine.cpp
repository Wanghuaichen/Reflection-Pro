#include "FieldDefine.h"

FieldDefine::FieldDefine()
{
}

FieldDefine::FieldDefine(QString name, QString type)
{
    this->name = name;
    this->type = type;
}

FieldDefine::FieldDefine(QString name, QString type, bool isKey)
{
    this->name = name;
    this->type = type;
    this->isKey = isKey;
}

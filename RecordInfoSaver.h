#ifndef RECORDINFOSAVER_H
#define RECORDINFOSAVER_H

#include "FieldDefine.h"
#include "InfoSaver.h"
#include "RecordInfo.h"

class RecordInfoSaver : public InfoSaver
{
public:
    RecordInfoSaver();
    virtual ~RecordInfoSaver();

    QList<FieldData> GetData(RecordInfo recordInfo);
    QList<FieldDefine> GetFieldList();
};

#endif // RECORDINFOSAVER_H

#ifndef REFLECTIONINFOSAVER_H
#define REFLECTIONINFOSAVER_H
#include "FieldDefine.h"
#include "InfoSaver.h"
#include "ReflectionInfo.h"

class ReflectionInfoSaver : public InfoSaver
{
public:
    ReflectionInfoSaver();
    virtual ~ReflectionInfoSaver();
    QList<FieldData> GetData(ReflectionInfo reflection);
};

#endif // REFLECTIONINFOSAVER_H

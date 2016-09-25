#ifndef IDATAACCESS_H
#define IDATAACCESS_H

#include "FieldDefine.h"

class IDataAccess
{
public:
    IDataAccess();
    virtual ~IDataAccess();
    virtual TableDefine GetTableDefine() = 0;
};

#endif // IDATAACCESS_H

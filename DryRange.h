#ifndef DRYRANGE_H
#define DRYRANGE_H
#include <QString.h>
#include "EnumReflectType.h"

struct Range
{
    float fLolimits;
    float fUplimits;
};



struct ReflectedRange
{
    eReflectType  eType;
    Range         fRanges;

    QString GetTypeString()
    {
        QString tstr = "";
        switch(eType)
        {
            case R:
                tstr = "R";
                break;
            case G:
                tstr = "G";
                break;
            case B:
                tstr = "B";
                break;
            case X:
                tstr = "X";
                break;
            case Y:
                tstr = "Y";
                break;
            case Z:
                tstr = "Z";
                break;
            default:
                break;
        }

        return tstr;
    }

    QString ToString()
    {
        QString tstr = this->GetTypeString();
        QString strLo;
        strLo.setNum(fRanges.fLolimits);
        QString strUp;
        strUp.setNum(fRanges.fUplimits);
        tstr += "[" + strLo + "#" + strUp + "]";
        return tstr;
    }
};

#endif // DRYRANGE_H

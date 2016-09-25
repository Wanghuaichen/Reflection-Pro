#ifndef DRYCOLORINFO_H
#define DRYCOLORINFO_H
#include <QString.h>
#include "EnumReflectType.h"

const static quint8 DryReflectNum = 15;

struct DryColor
{
    float Red;
    float Green;
    float Blue;

    inline QString ToString() const
    {
        QString red = "";
        red.setNum(Red);
        QString green = "";
        green.setNum(Green);
        QString blue = "";
        blue.setNum(Blue);
        return red.leftJustified(15, ' ') + green.leftJustified(15, ' ') + blue.leftJustified(15, ' ');
    }

    inline QString ToSmallString() const
    {
        return QString("%1 %2 %3").arg(this->Red).arg(this->Green).arg(this->Blue);
    }

    inline float GetValue(eReflectType type) const
    {
        float value = 0;
        switch(type)
        {
            case R:
                value = this->Red;
                break;
            case G:
                value = this->Green;
                break;
            case B:
                value = this->Blue;
                break;
            default:
                value = 0;
                break;
        }

        return value;
    }
};


struct DryReflectedSt
{
    DryColor ColorArray[DryReflectNum];

    inline QString ToString() const
    {
        QString reflectes = "\r\n";
        for(int i = 0; i < 15; ++i)
        {
            reflectes += (QString("L%1").arg(i + 1).leftJustified(3, ' ') + " = " + ColorArray[i].ToString() + "\r\n");
        }

        return reflectes;
    }
};

#endif // DRYCOLORINFO_H

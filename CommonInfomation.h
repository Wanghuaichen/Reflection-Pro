#ifndef COMMONINFOMATION_H
#define COMMONINFOMATION_H

#define DATESTYLE "yyyy-MM-dd"
#define TIMESTYLE "hh:mm"
#define ALERTSIGN "*"
#define EDITEDSIGN "E"
#define UNIT_MG "(mg/L)"
#define UNIT_ML "(mmol/L)"

typedef enum
{
    eUnitPlus = 0,
    eUnitCommon,
    eUnitInternational,
    eUnitAll,

}EnumUnitType;

typedef enum
{
    e11Items = 0,
    e12Items,
    e14Items,

}EnumItemCount;

#endif // COMMONINFOMATION_H

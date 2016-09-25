#ifndef ENUMPATIENTGENDERITEM_H
#define ENUMPATIENTGENDERITEM_H

#define FIRST_NAME_STRING "First Name"
#define LAST_NAME_STRING "Last Name"
#define BIRTHDAY_STRING "Date of Birth"
#define AGE_STRING "Age"
#define AGE_UNIT_STRING "Age Unit"
#define GENDER_STRING "Gender"
#define PATIENT_ID_STRING "Patient ID"
#define BARCODE_STRING "Bar Code"
#define RACKBARCODE_STRING "Rack Bar Code"
#define BED_NO_STRING "Bed No."
#define MEDICAL_INS_STRING "Medical Insurance"
#define DEPARTMENT_STRING "Department"
#define WARD_STRING "Ward"
#define DELIVERED_BY_STRING "Delivered by"
#define DELIEVERED_TIME_STRING "Delivered Time"
#define DRAWTIME_STRING "Draw Time"
#define DIAGNOSIS_STRING "Diagnosis"
#define PATIENT_TYPE_STRING "Patient Type"
#define CHARGE_TYPE_STRING "Charge Type"
#define COMMENTS_STRING "Comments"
#define CUSTOM1_STRING "Custom Field 1"
#define CUSTOM2_STRING "Custom Field 2"
#define CUSTOM3_STRING "Custom Field 3"
#define CUSTOM4_STRING "Custom Field 4"

typedef enum
{
    eGenderUnknown = 0,
    eMale,
    eFemale,

}eGenderItem;

typedef enum
{
    eYears = 0,
    eMonths,
    eDays,

}eAgeUnitItem;

#endif // ENUMPATIENTGENDERITEM_H

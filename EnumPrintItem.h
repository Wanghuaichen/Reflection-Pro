#ifndef ENUMPRINTITEM_H
#define ENUMPRINTITEM_H

enum EnumPrintGroupCtrl
{
    eGroupNull,
    ePatientInfo,
    eDryInfo,
    eOther,
};

enum EnumPrintPatientItem
{
    ePatientNull,
    eFirstName,
    eLastName,

    eGender,
    eAge,
    eDeliveredTime,
    eDrawTime,
    eCheckTime,
    eReportTime,
    eDelivereder,
    eChecker,
    eReviewer,
    eSampleId,
    eBarCode,
    eRackBarCode,
    ePatientId,
    eMedicalInstId,
    eDepartment,
    eBedNo,
    eDiagnosis,
    // eComments,
    eWard,
    eChemistryId,
    eSampleType,
    ePatientType,
    eChargeType,
    eBirthday,
    eDyeType,

    eEnableCustomField1,
    eEnableCustomField2,
    eEnableCustomField3,
    eEnableCustomField4,
};

enum EnumPrintExamItem
{
    eExamNull,
    eGroupTitle,
    eExamItem,
};

enum EnumSubPrintItem
{
    eSubNull,
    eItemName,
    eItemValue,
    eItemFlag,
    eItemRefRange,
    eItemLine,
};


enum EnumPrintOtherItem
{
    eOtherNull,
    eXLine,
    eYLine,
    eRemark,
    ePrompt,
    eReportTitle,
};



#endif // ENUMPRINTITEM_H

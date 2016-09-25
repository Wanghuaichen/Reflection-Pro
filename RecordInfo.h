#ifndef RECORDINFO_H
#define RECORDINFO_H

//#include "ResultInfo.h"
#include "CommonInfomation.h"
#include "EnumPrintItem.h"
#include "ReflectionInfo.h"
#include <QString>
#include <QMap>
#include <QDateTime>

class RecordInfo
{
public:
    RecordInfo();
    virtual ~RecordInfo();

    long    RecordIndex() const;
    long    OriResultIndex() const;
    long    CurResultIndex() const;
    long    ReflectionIndex() const;
    bool    IsFinished() const;
    bool    IsEmergency() const;
    bool    IsAlert() const;
    bool    IsQC() const;
    bool    IsMaintain() const;
    bool    IsValidated() const;
    bool    IsPrinted() const;
    bool    IsCommunicated() const;
    int     QuantifyType() const;
    EnumItemCount GetItemCount() const;
    QString SampleID() const;
    QString OperatedBy() const;
    QString ValidatedBy() const;
    QDate CheckDate() const;
    QTime CheckTime() const;
    QDateTime CheckDateTime() const;
    QString ReportTime() const;
    QString FirstName() const;
    QString LastName() const;
    QString DateOfBirth() const;
    QString Age() const;
    QString AgeUnit() const;
    QString Gender() const;
    QString PatientID() const;
    QString BarCode() const;
    QString RackBarCode() const;
    QString BedNo() const;
    QString MedicalInsurance() const;
    QString Department() const;
    QString Ward() const;
    QString DeliveredBy() const;
    QString DeliveredTime() const;
    QString DrawTime() const;
    QString Diagnosis() const;
    QString PatientType() const;
    QString ChargeType() const;
    QString Comments() const;
    QString CustomField1() const;
    QString CustomField2() const;
    QString CustomField3() const;
    QString CustomField4() const;
    QString GetAgeString();
    QString GetGenderString();
    const QMap<EnumPrintPatientItem, QString> GetPatientInfoDic() const;
    QString GetPatientInfo(EnumPrintPatientItem item);

    bool IsResultEmpty();
    void SetRecordIndex(long index);
    void SetOriResultIndex(long index);
    void SetCurResultIndex(long index);
    void SetReflectionIndex(long index);
    void SetIsFinished(bool finished);
    void SetIsEmergency(bool isEmergency);
    void SetIsAlert(bool isAlert);
    void SetIsQC(bool isQC);
    void SetIsMaintain(bool isMaintain);
    void SetIsValidated(bool isValidated);
    void SetIsPrinted(bool isPrinted);
    void SetIsCommunicated(bool isCommunicated);
    void SetQuantifyType(int type);
    void SetSampleID(QString id);
    void SetOperatedBy(QString operatedBy);
    void SetValidatedBy(QString validatedBy);
    void SetCheckDate(QDate checkDate);
    void SetCheckTime(QTime checkTime);
    void SetReportTime(QString reportTime);
    void SetFirstName(QString firstName);
    void SetLastName(QString lastName);
    void SetDateOfBirth(QString birthday);
    void SetAge(QString age);
    void SetAgeUnit(QString ageUnit);
    void SetGender(QString gender);
    void SetPatientID(QString id);
    void SetBarCode(QString barCode);
    void SetRackBarCode(const QString &rackBarCode);
    void SetBedNo(QString bedNo);
    void SetMedicalInsurance(QString medicalInsurance);
    void SetDepartment(QString department);
    void SetWard(QString ward);
    void SetDeliveredBy(QString deliveredBy);
    void SetDeliveredTime(QString deliveredTime);
    void SetDrawTime(QString drawTime);
    void SetDiagnosis(QString diagnosis);
    void SetPatientType(QString patientType);
    void SetChargeType(QString chargeType);
    void SetComments(QString comments);
    void SetCustomField1(QString custom1);
    void SetCustomField2(QString custom2);
    void SetCustomField3(QString custom3);
    void SetCustomField4(QString custom4);
    void SetItemCount(EnumItemCount itemCount);

    //ResultInfo *GetResult();
    //void SetResult(ResultInfo result);
    void SetValidateInfo(bool validated);
    ReflectionInfo* GetReflection();
    void SetReflection(ReflectionInfo reflectioninfo);
private:
    long m_recordIndex;
    long m_oriResultIndex;
    long m_curResultIndex;
    long m_reflectionIndex;
    bool m_isFinished;
    bool m_isEmergency;
    bool m_isAlert;
    bool m_isQC;
    bool m_isMaintain;
    bool m_isValidated;
    bool m_isPrinted;
    bool m_isCommunicated;
    int m_quantifyType;
    EnumItemCount m_itemCount;
    QString m_sampleID;
    QString m_operatedBy;
    QString m_validatedBy;
    QDate m_checkDate;
    QTime m_checkTime;
    QString m_reportTime;
    QString m_firstName;
    QString m_lastName;
    QString m_dateOfBirth;
    QString m_age;
    QString m_ageUnit;
    QString m_gender;
    QString m_patientID;
    QString m_barCode;
    QString m_rackBarCode;
    QString m_bedNo;
    QString m_medicalInsurance;
    QString m_department;
    QString m_ward;
    QString m_deliveredBy;
    QString m_deliveredTime;
    QString m_drawTime;
    QString m_diagnosis;
    QString m_patientType;
    QString m_chargeType;
    QString m_comments;
    QString m_customField1;
    QString m_customField2;
    QString m_customField3;
    QString m_customField4;

    //ResultInfo     m_result;
    ReflectionInfo m_reflection;
    QMap<EnumPrintPatientItem, QString>  m_dicPatientValue;
};

#endif // RECORDINFO_H

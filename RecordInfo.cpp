#include "RecordInfo.h"
#include "EnumPatientGenderItem.h"
#include "CommonInfomation.h"
//#include "CustomAgeEdit.h"
//#include "UserManager.h"

#include <QDateTime>

RecordInfo::RecordInfo()
{
    this->m_recordIndex = -1;
    this->m_oriResultIndex = -1;
    this->m_curResultIndex = -1;
    this->m_reflectionIndex = -1;
    this->m_quantifyType = 0;
    this->m_ageUnit = QString::number(eYears);
    this->m_gender = QString::number(eGenderUnknown);
    this->m_isFinished = false;
    this->m_isEmergency = false;
    this->m_isAlert = false;
    this->m_isQC = false;
    this->m_isMaintain = false;
    this->m_isValidated = false;
    this->m_isCommunicated = false;
    this->m_isPrinted = false;
    this->m_operatedBy = " ";//UserManager::GetInstance()->CurrentUser().getUserName();
    this->m_itemCount = e14Items;
}

RecordInfo::~RecordInfo()
{
}

long RecordInfo::RecordIndex() const
{
    return this->m_recordIndex;
}

long RecordInfo::OriResultIndex() const
{
    return this->m_oriResultIndex;
}

long RecordInfo::CurResultIndex() const
{
    return this->m_curResultIndex;
}

long RecordInfo::ReflectionIndex() const
{
    return this->m_reflectionIndex;
}

QString RecordInfo::SampleID() const
{
    return this->m_sampleID;
}

QString RecordInfo::OperatedBy() const
{
    return this->m_operatedBy;
}

QString RecordInfo::ValidatedBy() const
{
    return this->m_validatedBy;
}

QDate RecordInfo::CheckDate() const
{
    return this->m_checkDate;
}

QDateTime RecordInfo::CheckDateTime() const
{
    QDateTime dateTime;
    dateTime.setDate(this->m_checkDate);
    dateTime.setTime(this->m_checkTime);

    return dateTime;
}

QTime RecordInfo::CheckTime() const
{
    return this->m_checkTime;
}

QString RecordInfo::ReportTime() const
{
    return this->m_reportTime;
}

bool RecordInfo::IsFinished() const
{
    return this->m_isFinished;
}

bool RecordInfo::IsEmergency() const
{
    return this->m_isEmergency;
}

bool RecordInfo::IsAlert() const
{
    return this->m_isAlert;
}

bool RecordInfo::IsQC() const
{
    return this->m_isQC;
}

bool RecordInfo::IsMaintain() const
{
    return this->m_isMaintain;
}

bool RecordInfo::IsValidated() const
{
    return this->m_isValidated;
}

bool RecordInfo::IsPrinted() const
{
    return this->m_isPrinted;
}

bool RecordInfo::IsCommunicated() const
{
    return this->m_isCommunicated;
}

int RecordInfo::QuantifyType() const
{
    return this->m_quantifyType;
}

EnumItemCount RecordInfo::GetItemCount() const
{
    return this->m_itemCount;
}

QString RecordInfo::FirstName() const
{
    return this->m_firstName;
}

QString RecordInfo::LastName() const
{
    return this->m_lastName;
}

QString RecordInfo::DateOfBirth() const
{
    return this->m_dateOfBirth;
}

QString RecordInfo::Age() const
{
    return this->m_age;
}

QString RecordInfo::AgeUnit() const
{
    return this->m_ageUnit;
}

QString RecordInfo::Gender() const
{
    return this->m_gender;
}

QString RecordInfo::PatientID() const
{
    return this->m_patientID;
}

QString RecordInfo::BarCode() const
{
    return this->m_barCode;
}

QString RecordInfo::BedNo() const
{
    return this->m_bedNo;
}

QString RecordInfo::MedicalInsurance() const
{
    return this->m_medicalInsurance;
}

QString RecordInfo::Department() const
{
    return this->m_department;
}

QString RecordInfo::Ward() const
{
    return this->m_ward;
}

QString RecordInfo::DeliveredBy() const
{
    return this->m_deliveredBy;
}

QString RecordInfo::DeliveredTime() const
{
    return this->m_deliveredTime;
}

QString RecordInfo::DrawTime() const
{
    return this->m_drawTime;
}

QString RecordInfo::Diagnosis() const
{
    return this->m_diagnosis;
}

QString RecordInfo::PatientType() const
{
    return this->m_patientType;
}

QString RecordInfo::ChargeType() const
{
    return this->m_chargeType;
}

QString RecordInfo::Comments() const
{
    return this->m_comments;
}

QString RecordInfo::CustomField1() const
{
    return this->m_customField1;
}

QString RecordInfo::CustomField2() const
{
    return this->m_customField2;
}

QString RecordInfo::CustomField3() const
{
    return this->m_customField3;
}

QString RecordInfo::CustomField4() const
{
    return this->m_customField4;
}

QString RecordInfo::GetAgeString()
{
    QString unit;
    if (!this->m_age.isEmpty())
    {
        unit = " ";//CustomAgeEdit::GetUnitString((eAgeUnitItem)this->m_ageUnit.toInt());
    }

    return this->m_age + unit;
}

QString RecordInfo::GetGenderString()
{
    return " ";//CustomAgeEdit::GetGenderString((eGenderItem)this->m_gender.toInt());
}

const QMap<EnumPrintPatientItem, QString> RecordInfo::GetPatientInfoDic() const
{
    return this->m_dicPatientValue;
}

QString RecordInfo::GetPatientInfo(EnumPrintPatientItem item)
{
    if(this->m_dicPatientValue.contains(item))
    {
        return this->m_dicPatientValue.value(item);
    }
    else
    {
        return "";
    }
}

bool RecordInfo::IsResultEmpty()
{
    bool ret = false;
    /*ResultInfo* results = this->GetResult();
    if((0 == results) || (results->IsValueEmpty()))
    {
        ret = true;
    }*/

    return ret;
}

void RecordInfo::SetRecordIndex(long index)
{
    this->m_recordIndex = index;
}

void RecordInfo::SetOriResultIndex(long index)
{
    this->m_oriResultIndex = index;
}

void RecordInfo::SetCurResultIndex(long index)
{
    this->m_curResultIndex = index;
}

void RecordInfo::SetReflectionIndex(long index)
{
    this->m_reflectionIndex = index;
}

void RecordInfo::SetSampleID(QString id)
{
    this->m_sampleID = id;
    this->m_dicPatientValue[eSampleId] = id;
}

void RecordInfo::SetOperatedBy(QString operatedBy)
{
    this->m_operatedBy = operatedBy;
    this->m_dicPatientValue[eChecker] = operatedBy;
}

void RecordInfo::SetValidatedBy(QString validatedBy)
{
    this->m_validatedBy = validatedBy;
    this->m_dicPatientValue[eReviewer] = validatedBy;
}

void RecordInfo::SetCheckDate(QDate checkDate)
{
    this->m_checkDate = checkDate;
}

void RecordInfo::SetCheckTime(QTime checkTime)
{
    this->m_checkTime = checkTime;
    this->m_dicPatientValue[eCheckTime] = checkTime.toString();
}

void RecordInfo::SetReportTime(QString reportTime)
{
    this->m_reportTime = reportTime;
    this->m_dicPatientValue[eReportTime] = reportTime;
}

void RecordInfo::SetIsFinished(bool finished)
{
    this->m_isFinished = finished;
}

void RecordInfo::SetIsEmergency(bool isEmergency)
{
    this->m_isEmergency = isEmergency;
}

void RecordInfo::SetIsAlert(bool isAlert)
{
    this->m_isAlert = isAlert;
}

void RecordInfo::SetIsQC(bool isQC)
{
    this->m_isQC = isQC;
}

void RecordInfo::SetIsMaintain(bool isMaintain)
{
    this->m_isMaintain = isMaintain;
}

void RecordInfo::SetIsValidated(bool isValidated)
{
    this->m_isValidated = isValidated;
}

void RecordInfo::SetIsPrinted(bool isPrinted)
{
    this->m_isPrinted = isPrinted;
}

void RecordInfo::SetIsCommunicated(bool isCommunicated)
{
    this->m_isCommunicated = isCommunicated;
}

void RecordInfo::SetQuantifyType(int type)
{
    this->m_quantifyType = type;
}

void RecordInfo::SetFirstName(QString firstName)
{
    this->m_firstName = firstName;
    this->m_dicPatientValue[eFirstName] = firstName;
}

void RecordInfo::SetLastName(QString lastName)
{
    this->m_lastName = lastName;
    this->m_dicPatientValue[eLastName] = lastName;
}

void RecordInfo::SetDateOfBirth(QString birthday)
{
    this->m_dateOfBirth = birthday;
    this->m_dicPatientValue[eBirthday] = birthday;
}

void RecordInfo::SetAge(QString age)
{
    this->m_age = age;
    this->m_dicPatientValue[eAge] = age;
}

void RecordInfo::SetAgeUnit(QString ageUnit)
{
    this->m_ageUnit = ageUnit;
}

void RecordInfo::SetGender(QString gender)
{
    this->m_gender = gender;
    this->m_dicPatientValue[eGender] = gender;
}

void RecordInfo::SetPatientID(QString id)
{
    this->m_patientID = id;
    this->m_dicPatientValue[ePatientId] = id;
}

void RecordInfo::SetBarCode(QString barCode)
{
    this->m_barCode = barCode;
    this->m_dicPatientValue[eBarCode] = barCode;
}

void RecordInfo::SetBedNo(QString bedNo)
{
    this->m_bedNo = bedNo;
    this->m_dicPatientValue[eBedNo] = bedNo;
}

void RecordInfo::SetMedicalInsurance(QString medicalInsurance)
{
    this->m_medicalInsurance = medicalInsurance;
    this->m_dicPatientValue[eMedicalInstId] = medicalInsurance;
}

void RecordInfo::SetDepartment(QString department)
{
    this->m_department = department;
    this->m_dicPatientValue[eDepartment] = department;
}

void RecordInfo::SetWard(QString ward)
{
    this->m_ward = ward;
    this->m_dicPatientValue[eWard] = ward;
}

void RecordInfo::SetDeliveredBy(QString deliveredBy)
{
    this->m_deliveredBy = deliveredBy;
    this->m_dicPatientValue[eDelivereder] = deliveredBy;
}

void RecordInfo::SetDeliveredTime(QString deliveredTime)
{
    this->m_deliveredTime = deliveredTime;
    this->m_dicPatientValue[eDeliveredTime] = deliveredTime;
}

void RecordInfo::SetDrawTime(QString drawTime)
{
    this->m_drawTime = drawTime;
    this->m_dicPatientValue[eDrawTime] = drawTime;
}

void RecordInfo::SetDiagnosis(QString diagnosis)
{
    this->m_diagnosis = diagnosis;
    this->m_dicPatientValue[eDiagnosis] = diagnosis;
}

void RecordInfo::SetPatientType(QString patientType)
{
    this->m_patientType = patientType;
    this->m_dicPatientValue[ePatientType] = patientType;
}

void RecordInfo::SetChargeType(QString chargeType)
{
    this->m_chargeType = chargeType;
    this->m_dicPatientValue[eChargeType] = chargeType;
}

void RecordInfo::SetComments(QString comments)
{
    this->m_comments = comments;
}

void RecordInfo::SetCustomField1(QString custom1)
{
    this->m_customField1 = custom1;
    this->m_dicPatientValue[eEnableCustomField1] = custom1;
}

void RecordInfo::SetCustomField2(QString custom2)
{
    this->m_customField2 = custom2;
    this->m_dicPatientValue[eEnableCustomField2] = custom2;
}

void RecordInfo::SetCustomField3(QString custom3)
{
    this->m_customField3 = custom3;
    this->m_dicPatientValue[eEnableCustomField3] = custom3;
}

void RecordInfo::SetCustomField4(QString custom4)
{
    this->m_customField4 = custom4;
    this->m_dicPatientValue[eEnableCustomField4] = custom4;
}

void RecordInfo::SetItemCount(EnumItemCount itemCount)
{
    this->m_itemCount = itemCount;
}

/*ResultInfo *RecordInfo::GetResult()
{
    return &this->m_result;
}

void RecordInfo::SetResult(ResultInfo result)
{
    this->m_result = result;
}
*/
void RecordInfo::SetValidateInfo(bool validated)
{
    this->m_isValidated = validated;
    if (validated)
    {
        this->m_validatedBy = " ";//UserManager::GetInstance()->CurrentUser().getUserName();
    }
    else
    {
        this->m_validatedBy.clear();
    }
}

ReflectionInfo *RecordInfo::GetReflection()
{
    return &this->m_reflection;
}

void RecordInfo::SetReflection(ReflectionInfo reflectioninfo)
{
    this->m_reflection = reflectioninfo;
}

QString RecordInfo::RackBarCode() const
{
    return this->m_rackBarCode;
}

void RecordInfo::SetRackBarCode(const QString &rackBarCode)
{
    this->m_rackBarCode = rackBarCode;
    this->m_dicPatientValue[eRackBarCode] = rackBarCode;
}


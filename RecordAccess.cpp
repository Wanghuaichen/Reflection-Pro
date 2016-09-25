#include "RecordAccess.h"
#include "FieldDefine.h"
#include "RecordInfoSaver.h"
#include "RecordInfo.h"
#include "CommonInfomation.h"

#include <QList>
#include <QSqlRecord>

RecordAccess::RecordAccess()
{
}


RecordAccess::~RecordAccess()
{
}

TableDefine RecordAccess::GetTableDefine()
{
    return this->recordInfoSaver.table;
}

QList<FieldData> RecordAccess::GetData(RecordInfo record)
{
    return this->recordInfoSaver.GetData(record);
}

RecordInfo RecordAccess::ProcessSqlrecord(QSqlRecord sqlRecord)
{
    RecordInfo record;
    int index = 0;

    record.SetRecordIndex(sqlRecord.value(index++).toLongLong());
    record.SetOriResultIndex(sqlRecord.value(index++).toLongLong());
    record.SetCurResultIndex(sqlRecord.value(index++).toLongLong());
    record.SetIsFinished(sqlRecord.value(index++).toBool());
    record.SetIsEmergency(sqlRecord.value(index++).toBool());
    record.SetIsAlert(sqlRecord.value(index++).toBool());
    record.SetIsQC(sqlRecord.value(index++).toBool());
    record.SetIsMaintain(sqlRecord.value(index++).toBool());
    record.SetIsValidated(sqlRecord.value(index++).toBool());
    record.SetIsPrinted(sqlRecord.value(index++).toBool());
    record.SetIsCommunicated(sqlRecord.value(index++).toBool());
    record.SetQuantifyType(sqlRecord.value(index++).toInt());
    record.SetItemCount((EnumItemCount)(sqlRecord.value(index++).toInt()));
    record.SetSampleID(sqlRecord.value(index++).toString());
    record.SetOperatedBy(sqlRecord.value(index++).toString());
    record.SetValidatedBy(sqlRecord.value(index++).toString());

    record.SetCheckDate(sqlRecord.value(index++).toDate());
    record.SetCheckTime(sqlRecord.value(index++).toTime());

    record.SetReportTime(sqlRecord.value(index++).toString());
    record.SetFirstName(sqlRecord.value(index++).toString());
    record.SetLastName(sqlRecord.value(index++).toString());
    record.SetDateOfBirth(sqlRecord.value(index++).toString());
    record.SetAge(sqlRecord.value(index++).toString());
    record.SetAgeUnit(sqlRecord.value(index++).toString());
    record.SetGender(sqlRecord.value(index++).toString());
    record.SetPatientID(sqlRecord.value(index++).toString());
    record.SetBarCode(sqlRecord.value(index++).toString());
    record.SetBedNo(sqlRecord.value(index++).toString());
    record.SetMedicalInsurance(sqlRecord.value(index++).toString());
    record.SetDepartment(sqlRecord.value(index++).toString());
    record.SetWard(sqlRecord.value(index++).toString());
    record.SetDeliveredBy(sqlRecord.value(index++).toString());
    record.SetDeliveredTime(sqlRecord.value(index++).toString());
    record.SetDrawTime(sqlRecord.value(index++).toString());
    record.SetDiagnosis(sqlRecord.value(index++).toString());
    record.SetPatientType(sqlRecord.value(index++).toString());
    record.SetChargeType(sqlRecord.value(index++).toString());
    record.SetComments(sqlRecord.value(index++).toString());
    record.SetCustomField1(sqlRecord.value(index++).toString());
    record.SetCustomField2(sqlRecord.value(index++).toString());
    record.SetCustomField3(sqlRecord.value(index++).toString());
    record.SetCustomField4(sqlRecord.value(index++).toString());
    record.SetRackBarCode(sqlRecord.value(index++).toString());
    record.SetReflectionIndex(sqlRecord.value(index++).toLongLong());

    return record;
}

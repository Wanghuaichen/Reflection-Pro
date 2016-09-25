#include "RecordInfoSaver.h"
#include "FieldDefine.h"
#include "RecordInfo.h"

#include <QList>
#include <QString>

RecordInfoSaver::RecordInfoSaver()
{
    this->table.TableName = "record";
    this->table.Fields = this->GetFieldList();
}

RecordInfoSaver::~RecordInfoSaver()
{
}

QList<FieldDefine> RecordInfoSaver::GetFieldList()
{
    QList<FieldDefine> fields;

    fields << this->GetFieldDefine("recordIndex",      "integer primary key")
           << this->GetFieldDefine("oriResultIndex",   "bigint")
           << this->GetFieldDefine("curResultIndex",   "bigint")
           << this->GetFieldDefine("isFinished",       "bit")
           << this->GetFieldDefine("isEmergency",      "bit")
           << this->GetFieldDefine("isAlert",          "bit")
           << this->GetFieldDefine("isQC",             "bit")
           << this->GetFieldDefine("isMaintain",       "bit")
           << this->GetFieldDefine("isValidated",      "bit")
           << this->GetFieldDefine("isPrinted",        "bit")
           << this->GetFieldDefine("isCommunicated",   "bit")
           << this->GetFieldDefine("quantifyType",     "int")
           << this->GetFieldDefine("itemCount",        "int")
           << this->GetFieldDefine("sampleID",         "varchar(32)")
           << this->GetFieldDefine("operateDoctor",    "varchar(32)")
           << this->GetFieldDefine("validateDoctor",   "varchar(32)")
           << this->GetFieldDefine("checkDate",        "varchar(32)")
           << this->GetFieldDefine("checkTime",        "varchar(32)")
           << this->GetFieldDefine("reportTime",       "varchar(32)")
           << this->GetFieldDefine("firstName",        "varchar(32)")
           << this->GetFieldDefine("lastName",         "varchar(32)")
           << this->GetFieldDefine("dateOfBirth",      "varchar(32)")
           << this->GetFieldDefine("age",              "varchar(32)")
           << this->GetFieldDefine("ageUnit",          "varchar(32)")
           << this->GetFieldDefine("gender",           "varchar(32)")
           << this->GetFieldDefine("patientID",        "varchar(32)")
           << this->GetFieldDefine("barCode",          "varchar(32)")
           << this->GetFieldDefine("bedNo",            "varchar(32)")
           << this->GetFieldDefine("medicalInsurance", "varchar(32)")
           << this->GetFieldDefine("department",       "varchar(32)")
           << this->GetFieldDefine("ward",             "varchar(32)")
           << this->GetFieldDefine("deliveredBy",      "varchar(32)")
           << this->GetFieldDefine("deliveredTime",    "varchar(32)")
           << this->GetFieldDefine("drawTime",         "varchar(32)")
           << this->GetFieldDefine("diagnosis",        "varchar(32)")
           << this->GetFieldDefine("patientType",      "varchar(32)")
           << this->GetFieldDefine("chargeType",       "varchar(32)")
           << this->GetFieldDefine("comments",         "varchar(32)")
           << this->GetFieldDefine("customField1",     "varchar(32)")
           << this->GetFieldDefine("customField2",     "varchar(32)")
           << this->GetFieldDefine("customField3",     "varchar(32)")
           << this->GetFieldDefine("customField4",     "varchar(32)")
           << this->GetFieldDefine("rackBarCode",      "varchar(32)")
           << this->GetFieldDefine("curReflectionIndex",  "bigint");

    return fields;
}

QList<FieldData> RecordInfoSaver::GetData(RecordInfo recordInfo)
{
    QList<FieldData> recordData;

    recordData << this->MakeMap("oriResultIndex",    recordInfo.OriResultIndex())
               << this->MakeMap("curResultIndex",    recordInfo.CurResultIndex())
               << this->MakeMap("isFinished",        recordInfo.IsFinished())
               << this->MakeMap("isEmergency",       recordInfo.IsEmergency())
               << this->MakeMap("isAlert",           recordInfo.IsAlert())
               << this->MakeMap("isQC",              recordInfo.IsQC())
               << this->MakeMap("isMaintain",        recordInfo.IsMaintain())
               << this->MakeMap("isValidated",       recordInfo.IsValidated())
               << this->MakeMap("isPrinted",         recordInfo.IsPrinted())
               << this->MakeMap("isCommunicated",    recordInfo.IsCommunicated())
               << this->MakeMap("quantifyType",      recordInfo.QuantifyType())
               << this->MakeMap("itemCount",         recordInfo.GetItemCount())
               << this->MakeMap("sampleID",          recordInfo.SampleID())
               << this->MakeMap("operateDoctor",     recordInfo.OperatedBy())
               << this->MakeMap("validateDoctor",    recordInfo.ValidatedBy())
               << this->MakeMap("checkDate",         recordInfo.CheckDate())
               << this->MakeMap("checkTime",         recordInfo.CheckTime())
               << this->MakeMap("reportTime",        recordInfo.ReportTime())
               << this->MakeMap("firstName",         recordInfo.FirstName())
               << this->MakeMap("lastName",          recordInfo.LastName())
               << this->MakeMap("dateOfBirth",       recordInfo.DateOfBirth())
               << this->MakeMap("age",               recordInfo.Age())
               << this->MakeMap("ageUnit",           recordInfo.AgeUnit())
               << this->MakeMap("gender",            recordInfo.Gender())
               << this->MakeMap("patientID",         recordInfo.PatientID())
               << this->MakeMap("barCode",           recordInfo.BarCode())
               << this->MakeMap("bedNo",             recordInfo.BedNo())
               << this->MakeMap("medicalInsurance",  recordInfo.MedicalInsurance())
               << this->MakeMap("department",        recordInfo.Department())
               << this->MakeMap("ward",              recordInfo.Ward())
               << this->MakeMap("deliveredBy",       recordInfo.DeliveredBy())
               << this->MakeMap("deliveredTime",     recordInfo.DeliveredTime())
               << this->MakeMap("drawTime",          recordInfo.DrawTime())
               << this->MakeMap("diagnosis",         recordInfo.Diagnosis())
               << this->MakeMap("patientType",       recordInfo.PatientType())
               << this->MakeMap("chargeType",        recordInfo.ChargeType())
               << this->MakeMap("comments",          recordInfo.Comments())
               << this->MakeMap("customField1",      recordInfo.CustomField1())
               << this->MakeMap("customField2",      recordInfo.CustomField2())
               << this->MakeMap("customField3",      recordInfo.CustomField3())
               << this->MakeMap("customField4",      recordInfo.CustomField4())
               << this->MakeMap("rackBarCode",       recordInfo.RackBarCode())
               << this->MakeMap("curReflectionIndex",recordInfo.ReflectionIndex());

    return recordData;
}

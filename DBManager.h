#ifndef DBMANAGER_H
#define DBMANAGER_H
#define PATIENTDATAFILENAME "PatientData.db"
#define LOGDATAFILENAME "LogData.db"
#define QCDATAFILENAME "QCData.db"
#define QCMREFDATAFILENAME "QCMRefData.db"


#include "FieldDefine.h"
#include "Dbaccess.h"

#include <QMutex>
#include <QString>

class DBManager
{
public:
    DBManager();
    virtual ~DBManager();

protected:
    QMutex m_mutex;
    DBAccess m_dbaccess;
    QString m_sqlType;

    bool InitialDatabase(QString dbName);
    bool HasTable(TableDefine table);

};

#endif // DBMANAGER_H

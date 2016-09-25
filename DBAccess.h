#ifndef DBACCESS_H
#define DBACCESS_H
#include <QString>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsql.h>
#include <QDir>
#include "FieldDefine.h"
#include "QueryCondition.h"
class DBAccess
{
public:
    DBAccess();
    ~DBAccess();

    void CloseDatabase();
    bool OpenDataBase(QString dbName, QString dir, QString dbType);
    bool HasDBTable(TableDefine table);
    bool StartTransaction();
    bool HasTable(TableDefine table);
    bool ExecuteQString(QString message);
    bool CreatTable(TableDefine table);
    bool CommitTransaction();
    QList<QSqlRecord> GetRecordsByCondition(TableDefine table, QueryCondition condition);
    void QueryByCondition(TableDefine table, QueryCondition condition);
    QSqlRecord GetCurrentRecord();
    QString BindCondition(QueryCondition condition);
private:
    QSqlDatabase* m_pSqldb;
    QSqlQuery     m_query;
    QString       m_dbName;
    QString       m_dbDir;
    bool          m_opened;
    QMutex        m_mutex;

};

#endif // DBACCESS_H

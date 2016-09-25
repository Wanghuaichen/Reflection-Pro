#include "DBAccess.h"
#include <QFileInfo>
#include "ReflectionAccess.h"
DBAccess::DBAccess()
{
}

DBAccess::~DBAccess()
{
    if(NULL != this->m_pSqldb)
    {
        this->CloseDatabase();
        delete this->m_pSqldb;
        this->m_pSqldb = NULL;
    }
}

void DBAccess::CloseDatabase()
{
    if(0 != this->m_pSqldb)
    {
        if(this->m_pSqldb->isOpen())
        {
            this->m_pSqldb->close();
        }
    }

    this->m_opened = false;
}

bool DBAccess::OpenDataBase(QString dbName, QString dir, QString dbType)
{
    bool ret = false;
    QString dbfullPathName = dir + QDir::separator() + dbName;
    try
    {
        QFileInfo fileInfo(dbfullPathName);
        QDir dir = fileInfo.absoluteDir();
        ret = dir.mkpath(fileInfo.path());
        if(ret)
        {
            bool isPatientExists = true;
            if ("PatientData.db" == dbName)
            {
                isPatientExists = QFile::exists(dbfullPathName);
            }

            this->m_pSqldb = new QSqlDatabase(QSqlDatabase::addDatabase(dbType, dbName + "_" + dbType));
            this->m_pSqldb->setDatabaseName(dbfullPathName);
            this->m_opened = ret = this->m_pSqldb->open();
            if (ret)
            {
                this->m_query = QSqlQuery(*this->m_pSqldb);
            }

            if (!isPatientExists)
            {
                this->HasDBTable(ReflectionAccess().GetTableDefine());
                //this->SetDbVersion("200");
            }
        }
    }
    catch(QString exception)
    {
        this->m_opened = ret = false;
        /*QMessageBox message;
        message.setText(exception);
        message.show();*/
    }

    return ret;
}

bool DBAccess::HasDBTable(TableDefine table)
{
    bool success = false;
    this->m_mutex.lock();

    if (this->StartTransaction())
    {
        success = this->HasTable(table);

        if (!success)
        {
            success = this->CreatTable(table);
            if(success)
            {
                success = this->CommitTransaction();
            }
        }
    }

    this->m_mutex.unlock();
    return success;
}

bool DBAccess::StartTransaction()
{
    return this->m_pSqldb->transaction();
}

bool DBAccess::CommitTransaction()
{
    return this->m_pSqldb->commit();
}

bool DBAccess::HasTable(TableDefine table)
{
    bool success = false;

    QString message = QString("select count(*) from sqlite_master where type='table' and name ='%1'").arg(table.TableName);
    this->ExecuteQString(message);

    if (this->m_query.next())
    {
        if (this->m_query.value(0).toInt() != 0)
        {
            success = true;
        }
    }

    return success;
}

bool DBAccess::ExecuteQString(QString message)
{
    bool success = false;

    success = this->m_query.exec(message);
    //QSqlError error = this->m_query.lastError();

    return success;
}

bool DBAccess::CreatTable(TableDefine table)
{
    bool success = false;

    QString tableString = "create table ";
    tableString += table.TableName + "\n" + "(";

    foreach(FieldDefine fieldDefine, table.Fields)
    {
        QString stringList = "\n"
                            + fieldDefine.name
                            + " " + fieldDefine.type
                            + ",";

        tableString += stringList;
    }

    tableString.remove(tableString.length() - 1, 1);
    tableString += "\n";
    tableString += ")";

    success = this->ExecuteQString(tableString);

    success = success && this->HasTable(table);

    return success;
}

QList<QSqlRecord> DBAccess::GetRecordsByCondition(TableDefine table, QueryCondition condition)
{
    QList<QSqlRecord> dataList;
    this->QueryByCondition(table, condition);
    while (this->m_query.next())
    {
        dataList.append(this->GetCurrentRecord());
    }

    return dataList;
}

QSqlRecord DBAccess::GetCurrentRecord()
{
    return this->m_query.record();
}

void DBAccess::QueryByCondition(TableDefine table, QueryCondition condition)
{
    QString fields;
    for (int i = 0; i < table.Fields.length(); i++)
    {
        fields += table.Fields[i].name;
        if (i != table.Fields.length() - 1)
        {
            // not the last item.
            fields += ", ";
        }
    }

    QString tableString = "select " + fields + " from " + table.TableName;
    tableString.append(this->BindCondition(condition));
    this->ExecuteQString(tableString);
}

QString DBAccess::BindCondition(QueryCondition condition)
{
    QString conditonString;
    int count = condition.GetConditiaonList().count();

    if (count > 0)
    {
        conditonString = " where ";

        for (int i = 0; i < count; i++)
        {
            ConditionItem item = condition.GetConditiaonList()[i];

            if (i > 0)
            {
                conditonString += item.LogicalOperator;
            }

            conditonString += item.FieldName + " " +
                              item.CompareOperator + " " +
                              item.Data.toString();
        }
    }

    return conditonString;
}

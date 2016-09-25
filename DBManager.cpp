#include "DBManager.h"
#include "filepathmanager.h"

#include <QMutex>

DBManager::DBManager()
{
    this->m_sqlType = "QSQLITE";
}

DBManager::~DBManager()
{
}

bool DBManager::InitialDatabase(QString dbName)
{
    QMutexLocker locker(&this->m_mutex);
    bool success = false;

    FilePathManager fileMng;
    success = this->m_dbaccess.OpenDataBase(dbName, fileMng.GetPatientDataPath(), this->m_sqlType);

    return success;
}

bool DBManager::HasTable(TableDefine table)
{
    bool success = false;
    this->m_mutex.lock();

    if (this->m_dbaccess.StartTransaction())
    {
        success = this->m_dbaccess.HasTable(table);

        if (!success)
        {
            success = this->m_dbaccess.CreatTable(table);
        }

        if (success)
        {
            success = this->m_dbaccess.CommitTransaction();
        }
    }

    this->m_mutex.unlock();
    return success;
}

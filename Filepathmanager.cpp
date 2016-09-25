#include "filepathmanager.h"
//#include "IniAccess.h"
#include "qcoreapplication.h"
//#include "MessageContext.h"
//#include "CommonMessage.h"

#include <QDir>
#include <QDebug>

FilePathManager::FilePathManager() :
    m_canShowFrameTitle(true),
    m_minSize(0),
    m_warningSize(0)
{
#ifdef Q_OS_WIN32
    this->productDataPath = "D:\\UA-Series";
#elif Q_OS_LINUX
    this->productDataPath = "/UA-Series";
#endif

    //this->ReadRootPath();
    this->rootPath = "C:\\Program Files\\mindray\\UA-Series";//"D:\\Users\\liuzhongxin\\Documents\\QtProject\\reflection\\reflection";

}

QString FilePathManager::GetPicturePath()
{
    QString path = this->rootPath + "/pictures";
    this->CreateDir(path);
    return path;
}

QString FilePathManager::GetLanguagesPath()
{
    QString path = this->rootPath + "/languages";
    this->CreateDir(path);
    return path;
}

QString FilePathManager::GetFactoryPresetPath()
{
    QString path = this->rootPath + "/preset/factory";
    this->CreateDir(path);
    return path;
}

QString FilePathManager::GetCurrentPresetPath()
{
    QString path = this->productDataPath + QDir::separator() + "preset" + QDir::separator() + "current";
    this->CreateDir(path);
    return path;
}

QString FilePathManager::GetPatientDataPath()
{
    QString path = this->productDataPath + QDir::separator() + "patientdata";
    this->CreateDir(path);
    return path;
}

QString FilePathManager::GetLogPath()
{
    QString path = this->productDataPath + QDir::separator() + "logs";
    this->CreateDir(path);
    return path;
}

QString FilePathManager::ConfigurePath()
{
    QString path = this->rootPath + QDir::separator() + "configure";
    this->CreateDir(path);
    return path;
}

QString FilePathManager::GetDeliverPath()
{
    QString path = this->productDataPath + QDir::separator() + "deliver";
    this->CreateDir(path);
    return path;
}

QString FilePathManager::GetReportPath()
{
    return this->ConfigurePath() + QDir::separator() + "Reports";
}

bool FilePathManager::CanShowFrameTitle()
{
    return this->m_canShowFrameTitle;
}

quint64 FilePathManager::GetMinSize()
{
    return this->m_minSize;
}

quint64 FilePathManager::GetWarningSize()
{
    return this->m_warningSize;
}

bool FilePathManager::GetReagentSWVisible()
{
    return this->m_reagentSWVisible;
}

bool FilePathManager::CreateDir(QString path)
{
    bool success = true;

    QDir dir(path);
    if (!dir.exists())
    {
        qDebug() << "No path: " + path;
        success = dir.mkdir(path);
    }

    return success;
}

/*void FilePathManager::ReadRootPath()
{
    QString curPath = QCoreApplication::applicationDirPath();

    QString iniFilePath = curPath + "/envconfig.ini";

    QFile file(iniFilePath);
    if (file.exists())
    {
        IniAccess iniAccess(iniFilePath);

        QString tempRootPath = iniAccess.Read("Path", "RootPath");
        if (tempRootPath.length() == 0)
        {
            tempRootPath = curPath;
        }

        this->m_canShowFrameTitle = iniAccess.Read("Window", "ShowTitle").toUpper() == "TRUE";
        this->m_minSize = iniAccess.Read("Disk", "MinSize").toUpper().toLongLong();
        this->m_warningSize = iniAccess.Read("Disk", "WarningSize").toLower().toLongLong();
        this->rootPath = tempRootPath;
        this->m_reagentSWVisible = iniAccess.Read("ReagentSWVisible", "ReagentSWVisible").toInt();
    }
    else
    {
        qDebug()<<"Error: cannot find envconfig.ini file!";
    }
}*/

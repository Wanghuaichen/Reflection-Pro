#ifndef FILEPATHMANAGER_H
#define FILEPATHMANAGER_H
#define CUSTOM_SEPARATOR "/"

#include <QString>

class FilePathManager
{
public:
    FilePathManager();

    QString GetPicturePath();
    QString GetLanguagesPath();
    QString GetFactoryPresetPath();
    QString GetCurrentPresetPath();
    QString GetPatientDataPath();
    QString GetLogPath();
    QString ConfigurePath();
    QString GetDeliverPath();
    QString GetReportPath();

    bool CanShowFrameTitle();
    quint64 GetMinSize();
    quint64 GetWarningSize();
    bool    GetReagentSWVisible();
private:
    QString rootPath;
    QString productDataPath;
    bool m_canShowFrameTitle;
    quint64  m_minSize;
    quint64 m_warningSize ;
    bool    m_reagentSWVisible;
    bool CreateDir(QString path);
    //void ReadRootPath();
};

#endif // FILEPATHMANAGER_H

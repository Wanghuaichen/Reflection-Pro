#include "UIWidthManager.h"
#include "filepathmanager.h"
#include "IniAccess.h"
//#include "LanguageManager.h"

#include <QFile>
#include <QDebug>

UIWidthManager *UIWidthManager::GetInstance()
{
    static UIWidthManager instance;
    return &instance;
}

QList<int> UIWidthManager::GetWidthOfTable(QString name)
{
    QList<int> list;

    FilePathManager filePathMng;
    QString uiWidthFile = filePathMng.ConfigurePath() + "/UIWidth.ini";

    QString language = "zh-CN";//LanguageManager::GetInstance()->GetLanguageTypeString();
    QFile file(uiWidthFile);
    if (file.exists())
    {
        IniAccess iniAccess(uiWidthFile);
        QString widthString = iniAccess.Read(name, language);
        QStringList widths = widthString.split(' ');

        for (int i = 0; i < widths.length(); ++i)
        {
            int w = 0;
            w = widths[i].toInt();
            if (w != 0)
            {
                list.append(w);
            }
        }
    }

    return list;
}

UIWidthManager::UIWidthManager()
{
}

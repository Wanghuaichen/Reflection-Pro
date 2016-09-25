#ifndef UIWIDTHMANAGER_H
#define UIWIDTHMANAGER_H

#include <QString>
#include <QList>

class UIWidthManager
{
public:
    static UIWidthManager *GetInstance();
    QList<int> GetWidthOfTable(QString name);

private:
    UIWidthManager();
};

#endif // UIWIDTHMANAGER_H

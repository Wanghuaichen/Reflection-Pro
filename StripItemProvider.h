#ifndef STRIPITEMPROVIDER_H
#define STRIPITEMPROVIDER_H
#include <QMap>
#include "EnumChemistryType.h"

class StripItemProvider
{
public:
    StripItemProvider();
    virtual ~StripItemProvider();
    bool TryReLoadStripItem();
    bool LoadStripItem();
    int GetItemIndex(EnumChemistryType type);
    bool GetTypeByIndex(int index, EnumChemistryType& type);
    quint16 CurStripItemCount() const;
protected:
    void Init();
    bool Load(QString filePathName);
    void RegisterExamItem(QString name, EnumChemistryType item);
    bool Check();

private:
    QMap<EnumChemistryType, int>     m_dicStripItem;
    QMap<int, QString>               m_dicItemfileName;
    QMap<QString, EnumChemistryType> m_dicExamName;

};

#endif // STRIPITEMPROVIDER_H

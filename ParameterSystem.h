#ifndef PARAMETERSYSTEM_H
#define PARAMETERSYSTEM_H

#include <QMap>
#include <QString>
#include <QXmlStreamReader>
#include "EnumChemistryType.h"
#include "CommonInfomation.h"


struct ChemistryMapItem
{
    QString ConventionalValue;
    QString InternationalValue;
};

typedef enum
{
    eRefNoneAlert = 0,
    eRefMinAlert,
    eRefNegtiveAlert,
    eRefListAlert,

}EnumParmRefType;

class ParameterSystem
{
public:
    static ParameterSystem* Instance();
    virtual ~ParameterSystem();

    QMap<QString, QMap<QString, ChemistryMapItem>> ParamList() const;
    QMap<QString, QMap<int, QString>> ParamQuantifySortList() const;
    QMap<int, QString> ParamQuantifySortListByType(EnumChemistryType type) const;

    QMap<QString, EnumParmRefType> GetRefList() const;
    QString GetRefString(EnumChemistryType type);
    QList<QString> GetRefList(EnumChemistryType type);
    QString GetKeyNameByType(EnumChemistryType type);
    QString GetShowNameByType(EnumChemistryType type);
    EnumChemistryType GetTypeByKeyName(QString keyName);
    QList<EnumChemistryType> GetParamSortList() const;
    QList<EnumChemistryType> GetUnshowParmList(EnumItemCount itemCount);
    QString GetRefString(EnumParmRefType refType, QString paramName) const;
    QString GetShowingMultiLanguageValue(QString value);

    QString GetRefPlusString(EnumParmRefType refType, QString paramName) const;
    QString GetRefConString(EnumParmRefType refType, QString paramName) const;
    QString GetRefInterString(EnumParmRefType refType, QString paramName) const;

private:
    QList<EnumChemistryType> m_paramSortList;
    QMap<QString, QMap<QString, ChemistryMapItem>> m_paramList;
    QMap<QString, EnumParmRefType> m_refList;
    QMap<QString, QList<QString>> m_refRangeList;
    QMap<QString, QString> m_refStringList;
    QMap<QString, QString> m_refPlusStringList;
    QMap<QString, QString> m_refConStringList;
    QMap<QString, QString> m_refInterStringList;
    QMap<QString, QMap<int, QString>> m_paramQuantifySortList;
    QMap<EnumChemistryType, QString> m_typeToKeyNameMap;
    QMap<EnumChemistryType, QString> m_typeToShowNameMap;
    QMap<QString, QString> m_valueToLanguageMap;

    ParameterSystem();
    void ContentToList(QList<QString> contentList);
    void LoadParameterXml(QString paramFile);
    void InitialParameters();
    void InitMap();
    void InitSortList();
    void InitValueToLanguage();
};

#endif // PARAMETERSYSTEM_H

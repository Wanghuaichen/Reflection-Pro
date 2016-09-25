#include "ParameterSystem.h"
#include "filepathmanager.h"
#include "CommonInfomation.h"
//#include "systempreset.h"
//#include "LanguageManager.h"
#include "CommonInfomation.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QMap>
#include <QCoreApplication>
#include <QDir>

ParameterSystem::ParameterSystem()
{
    this->InitSortList();
    this->InitMap();
    this->InitialParameters();
    this->InitValueToLanguage();
}

ParameterSystem::~ParameterSystem()
{
}

QMap<QString, QMap<QString, ChemistryMapItem> > ParameterSystem::ParamList() const
{
    return this->m_paramList;
}

QMap<QString, QMap<int, QString> > ParameterSystem::ParamQuantifySortList() const
{
    return this->m_paramQuantifySortList;
}

QMap<int, QString> ParameterSystem::ParamQuantifySortListByType(EnumChemistryType type) const
{
    QMap<int, QString> paralist;
    QString strName;
    if(this->m_typeToKeyNameMap.contains(type))
    {
        strName = this->m_typeToKeyNameMap[type];
    }

    if(!strName.isNull() && !strName.isEmpty())
    {
        paralist = this->m_paramQuantifySortList[strName];
    }

    return paralist;
}

QMap<QString, EnumParmRefType> ParameterSystem::GetRefList() const
{
    return this->m_refList;
}

QString ParameterSystem::GetRefString(EnumChemistryType type)
{
    QString name = this->GetKeyNameByType(type);
    QString refString;
    if (this->m_refStringList.contains(name))
    {
        refString = this->m_refStringList[name];
    }

    return refString;
}

QList<QString> ParameterSystem::GetRefList(EnumChemistryType type)
{
    QString name = this->GetKeyNameByType(type);
    QList<QString> list;
    if (this->m_refRangeList.contains(name))
    {
        list = this->m_refRangeList[name];
    }

    return list;
}

QString ParameterSystem::GetKeyNameByType(EnumChemistryType type)
{
    QString result;
    if (this->m_typeToKeyNameMap.contains(type))
    {
        result = this->m_typeToKeyNameMap[type];
    }

    return result;
}

QString ParameterSystem::GetShowNameByType(EnumChemistryType type)
{
    QString result;
    if (this->m_typeToShowNameMap.contains(type))
    {
        result = this->m_typeToShowNameMap[type];
    }

    return result;
}

EnumChemistryType ParameterSystem::GetTypeByKeyName(QString keyName)
{
    EnumChemistryType result = LEU;
    keyName.remove(".");

    QMap<EnumChemistryType, QString>::iterator itea = this->m_typeToKeyNameMap.begin();
    for (; itea != this->m_typeToKeyNameMap.end(); ++itea)
    {
        if (itea.value() == keyName)
        {
            result = itea.key();
            break;
        }
    }

    return result;
}

QList<EnumChemistryType> ParameterSystem::GetUnshowParmList(EnumItemCount itemCount)
{
    QList<EnumChemistryType> unshowItemList;

    switch(itemCount)
    {
    case e11Items:
        unshowItemList.append(MCA);
        unshowItemList.append(CRE);
        unshowItemList.append(CA);
        break;
    case e12Items:
        unshowItemList.append(CRE);
        unshowItemList.append(CA);
        break;
    default:
        break;
    }

    return unshowItemList;
}

QList<EnumChemistryType> ParameterSystem::GetParamSortList() const
{
    return this->m_paramSortList;
}

QString ParameterSystem::GetRefPlusString(EnumParmRefType refType, QString paramName) const
{
    QString strRef = "";
    if (this->m_refPlusStringList.contains(paramName))
    {
        strRef = this->m_refPlusStringList[paramName];
    }

    if (strRef.isEmpty())
    {
        strRef = this->GetRefString(refType, paramName);
    }

    return strRef;
}

QString ParameterSystem::GetRefConString(EnumParmRefType refType, QString paramName) const
{
    QString strRef = "";
    if (this->m_refConStringList.contains(paramName))
    {
        strRef = this->m_refConStringList[paramName];
    }

    if (strRef.isEmpty())
    {
        strRef = this->GetRefString(refType, paramName);
    }

    return strRef;
}

QString ParameterSystem::GetRefInterString(EnumParmRefType refType, QString paramName) const
{
    QString strRef = "";
    if (this->m_refInterStringList.contains(paramName))
    {
        strRef = this->m_refInterStringList[paramName];
    }

    if (strRef.isEmpty())
    {
        strRef = this->GetRefString(refType, paramName);
    }

    return strRef;
}

QString ParameterSystem::GetRefString(EnumParmRefType refType, QString paramName) const
{
    QString strRef = "";
    switch(refType)
    {
    case eRefNoneAlert:
        strRef = "";
        break;

    case eRefMinAlert:
        strRef = "norm.";
        break;

    case eRefNegtiveAlert:
        strRef = "neg.";
        break;

    case eRefListAlert:
        if (this->m_refStringList.contains(paramName))
        {
            strRef = this->m_refStringList[paramName];
        }

        break;

    default:
        break;
    }

    return strRef;
}

QString ParameterSystem::GetShowingMultiLanguageValue(QString value)
{
    QString result;
    if (this->m_valueToLanguageMap.contains(value))
    {
        result = this->m_valueToLanguageMap[value];
    }
    else
    {
        result = value;
    }

    return result;
}

ParameterSystem* ParameterSystem::Instance()
{
    static ParameterSystem instance;
    return &instance;
}

void ParameterSystem::InitialParameters()
{
    FilePathManager filePahtMng;
    QString paramFile = filePahtMng.ConfigurePath() + QDir::separator() + "Parameters.xml";
    this->LoadParameterXml(paramFile);
}

void ParameterSystem::InitMap()
{
    this->m_typeToKeyNameMap.insert(LEU, "LEU");
    this->m_typeToKeyNameMap.insert(URO, "URO");
    this->m_typeToKeyNameMap.insert(MCA, "MCA");
    this->m_typeToKeyNameMap.insert(PRO, "PRO");
    this->m_typeToKeyNameMap.insert(BIL, "BIL");
    this->m_typeToKeyNameMap.insert(GLU, "GLU");
    this->m_typeToKeyNameMap.insert(VC, "VitC");
    this->m_typeToKeyNameMap.insert(SG, "SG");
    this->m_typeToKeyNameMap.insert(KET, "KET");
    this->m_typeToKeyNameMap.insert(NIT, "NIT");
    this->m_typeToKeyNameMap.insert(CRE, "CRE");
    this->m_typeToKeyNameMap.insert(PH, "pH");
    this->m_typeToKeyNameMap.insert(BLD, "BLD");
    this->m_typeToKeyNameMap.insert(CA, "CA");
    this->m_typeToKeyNameMap.insert(Color, "Color");
    this->m_typeToKeyNameMap.insert(Turbidity, "Turb");

    this->m_typeToShowNameMap.insert(LEU, "LEU");
    this->m_typeToShowNameMap.insert(URO, "URO");
    this->m_typeToShowNameMap.insert(MCA, "MCA");
    this->m_typeToShowNameMap.insert(PRO, "PRO");
    this->m_typeToShowNameMap.insert(BIL, "BIL");
    this->m_typeToShowNameMap.insert(GLU, "GLU");
    this->m_typeToShowNameMap.insert(VC, "VitC");
    this->m_typeToShowNameMap.insert(SG, "S.G.");
    this->m_typeToShowNameMap.insert(KET, "KET");
    this->m_typeToShowNameMap.insert(NIT, "NIT");
    this->m_typeToShowNameMap.insert(CRE, "CRE");
    this->m_typeToShowNameMap.insert(PH, "pH");
    this->m_typeToShowNameMap.insert(BLD, "BLD");
    this->m_typeToShowNameMap.insert(CA, "CA");
    this->m_typeToShowNameMap.insert(Color, "Color");
    this->m_typeToShowNameMap.insert(Turbidity, "Turb.");
}

void ParameterSystem::InitSortList()
{
    this->m_paramSortList.append(LEU);
    this->m_paramSortList.append(URO);
    this->m_paramSortList.append(MCA);
    this->m_paramSortList.append(PRO);
    this->m_paramSortList.append(BIL);
    this->m_paramSortList.append(GLU);
    this->m_paramSortList.append(VC);
    this->m_paramSortList.append(SG);
    this->m_paramSortList.append(KET);
    this->m_paramSortList.append(NIT);
    this->m_paramSortList.append(CRE);
    this->m_paramSortList.append(PH);
    this->m_paramSortList.append(BLD);
    this->m_paramSortList.append(CA);
    this->m_paramSortList.append(Color);
    this->m_paramSortList.append(Turbidity);
}

void ParameterSystem::InitValueToLanguage()
{
    /*this->m_valueToLanguageMap.insert("Colorless", TR("Colorless"));
    this->m_valueToLanguageMap.insert("Yellow", TR("Yellow"));
    this->m_valueToLanguageMap.insert("Dark Yellow", TR("Dark Yellow"));
    this->m_valueToLanguageMap.insert("Pink", TR("Pink"));
    this->m_valueToLanguageMap.insert("Red", TR("Red#01"));
    this->m_valueToLanguageMap.insert("Blue", TR("Blue"));
    this->m_valueToLanguageMap.insert("Green", TR("Green#01"));
    this->m_valueToLanguageMap.insert("Other", TR("Other#02"));
    this->m_valueToLanguageMap.insert("Clear", TR("Clear#01"));
    this->m_valueToLanguageMap.insert("Slight Turbid", TR("Slight Turbid"));
    this->m_valueToLanguageMap.insert("Severe Turbid", TR("Severe Turbid"));*/
}

void ParameterSystem::LoadParameterXml(QString paramFile)
{
    QList<QString> contentList;
    QFile file(paramFile);

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        this->m_paramList.clear();
        this->m_paramQuantifySortList.clear();
        this->m_refList.clear();
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);

        while(!xmlReader.atEnd()&& !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType type = xmlReader.readNext();

            if(QXmlStreamReader::StartElement == type)
            {
                contentList.append(xmlReader.name().toString());
                if (xmlReader.attributes().hasAttribute("key"))
                {
                    contentList.append(xmlReader.attributes().value("key").toString());
                }
            }
            else if (QXmlStreamReader::EndElement == type)
            {
                contentList.append("/" + xmlReader.name().toString());
            }
            else if (QXmlStreamReader::Characters == type && !xmlReader.isWhitespace())
            {
                contentList.append(xmlReader.text().toString());
            }
        }
    }

    file.close();
    this->ContentToList(contentList);
}

void ParameterSystem::ContentToList(QList<QString> contentList)
{
    QString name;
    QString key;
    EnumParmRefType refType;
    ChemistryMapItem item;
    QMap<QString, ChemistryMapItem> map;
    QMap<int, QString> sortMap;
    QList<QString> refList;
    QString refString;
    QString refPlusString;
    QString refConString;
    QString refInterString;
    int index = 0;
    for (int i =0; i < contentList.count(); i++)
    {
        if ("Parameter" == contentList[i])
        {
            name.clear();
            map.clear();
            sortMap.clear();
            index = 0;
            refType = eRefNoneAlert;
            refList.clear();
            refString.clear();
            refPlusString.clear();
            refConString.clear();
            refInterString.clear();
        }
        else if ("Name" == contentList[i])
        {
            name = contentList[++i];
        }
        else if ("Ref" == contentList[i])
        {
            refType = (EnumParmRefType)(contentList[++i].toInt());
        }
        else if ("RefString" == contentList[i])
        {
            refString = contentList[++i];
        }
        else if ("RefPlusString" == contentList[i])
        {
            refPlusString = contentList[++i];
        }
        else if ("RefConString" == contentList[i])
        {
            refConString = contentList[++i];
        }
        else if ("RefInterString" == contentList[i])
        {
            refInterString = contentList[++i];
        }
        else if ("RefItem" == contentList[i])
        {
            refList.append(contentList[++i]);
        }
        else if ("Pair" == contentList[i])
        {
            key = contentList[++i];
            item.ConventionalValue.clear();
            item.InternationalValue.clear();
        }
        else if ("ConventionalValue" == contentList[i] && "/ConventionalValue" != contentList[i+1])
        {
            item.ConventionalValue = contentList[++i];
        }
        else if ("InternationalValue" == contentList[i] && "/InternationalValue" != contentList[i+1])
        {
            item.InternationalValue = contentList[++i];
        }
        else if ("/Parameter" == contentList[i])
        {
            this->m_paramList.insert(name, map);
            this->m_paramQuantifySortList.insert(name,sortMap);
            this->m_refList.insert(name, refType);
            this->m_refRangeList.insert(name, refList);
            this->m_refStringList.insert(name, refString);
            this->m_refPlusStringList.insert(name, refPlusString);
            this->m_refConStringList.insert(name, refConString);
            this->m_refInterStringList.insert(name, refInterString);
        }
        else if ("/Pair" == contentList[i])
        {
            map.insert(key, item);
            sortMap.insert(index++, key);
        }
    }
}

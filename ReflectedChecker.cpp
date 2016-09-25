#include "ReflectedChecker.h"
#include "filepathmanager.h"
#include "IniAccess.h"
//#include "setuppreset.h"
//#include "logsystem.h"

#include <QDir>
#include <QDebug>

const QString ITEM_SECTION = "ITEM";



ReflectedChecker::ReflectedChecker(QObject *parent) :
    QObject(parent),
    m_overNumLow(1),
    m_overNumUp(1)
{
    this->Init();
}

ReflectedChecker::~ReflectedChecker()
{
    qDeleteAll(this->m_dicDryCorrectTable);
    this->m_dicDryCorrectTable.clear();

    this->m_dicExamName.clear();
    this->m_dicColorType.clear();
}

ReflectedChecker::ReflectState ReflectedChecker::Check(const DryReflectedSt *dryReflect)
{
    ReflectState ret = ReflectOK;
    if(0 == dryReflect)
    {
        ret = ReflectNULL;
    }
    else
    {
        int lowOverCount = 0;
        int upOverCount = 0;
        for(int type = 0; type < (int)Turbidity; ++type)
        {
            const QMap<eReflectType, ReflectedRange*>* pdicMap = this->GetCorrectMap((EnumChemistryType)type);
            int colorIndex = this->m_stripProvider.GetItemIndex((EnumChemistryType)type);
            if((0 != pdicMap) && (-1 != colorIndex))
            {
                DryColor colorWeight = dryReflect->ColorArray[colorIndex];
                ret = this->CalcCheck(colorWeight, pdicMap);
                if(ReflectOK != ret)
                {
                    QString log = "OVER:" + QString::number(type);
                    //LogSystem::Instance()->Write(DryData, log);
                }

                if (ReflectLowOVER == ret)
                {
                    lowOverCount++;
                }

                if (ReflectUpOVER == ret)
                {
                    upOverCount++;
                }

                ret = this->CheckReflectCount(lowOverCount, upOverCount);
            }
        }
    }

    return ret;
}

ReflectedChecker::ReflectState ReflectedChecker::CheckReflectCount(int lowOverCount, int upOverCount)
{
    ReflectState ret = ReflectOK;

    int overNumLow = this->m_overNumLow;
    int overNumUp = this->m_overNumUp;

    if (lowOverCount >= overNumLow)
    {
        ret = ReflectLowOVER;
    }

    if (upOverCount >= overNumUp)
    {
        ret = ReflectUpOVER;
    }

    return ret;
}

void ReflectedChecker::LoadOverReflectNum()
{
    QString head = "OverReflect";
    IniAccess access(this->m_path);
    QString lowString = access.Read(head, "OverReflectNumForLow");
    QString upString = access.Read(head, "OverReflectNumForUp");
    this->m_overNumLow = lowString.toInt();
    this->m_overNumUp = upString.toInt();
}

void ReflectedChecker::Init()
{
    // 1 register Exam
    this->m_dicExamName[LEU] = "LEU";
    this->m_dicExamName[URO] = "URO";
    this->m_dicExamName[MCA] = "MCA";
    this->m_dicExamName[PRO] = "PRO";
    this->m_dicExamName[BIL] = "BIL";
    this->m_dicExamName[GLU] = "GLU";
    this->m_dicExamName[VC]  = "VC";
    this->m_dicExamName[SG]  = "SG";
    this->m_dicExamName[KET] = "KET";
    this->m_dicExamName[NIT] = "NIT";
    this->m_dicExamName[CRE] = "CRE";
    this->m_dicExamName[PH]  = "PH";
    this->m_dicExamName[BLD] = "BLD";
    this->m_dicExamName[CA]  = "CA";
    this->m_dicExamName[Color]  = "Color";

    // 2 register color
    this->m_dicColorType[QString("R")] = R;
    this->m_dicColorType[QString("G")] = G;
    this->m_dicColorType[QString("B")] = B;
    //
    FilePathManager  filePathMng;
    this->m_path = filePathMng.ConfigurePath() + QDir::separator() + "DryReflectionCorrectTable.ini";
    this->LoadMap();
    this->LoadOverReflectNum();
}

bool ReflectedChecker::LoadMap()
{
    QFileInfo fi(this->m_path);
    if(fi.isFile())
    {
        for (int i = 0; i < (int)Turbidity; ++i)
        {
            EnumChemistryType dryItem = (EnumChemistryType)i;
            if(this->m_dicExamName.contains(dryItem))
            {
                QString sectionName = this->m_dicExamName.value(dryItem);
                QMap<eReflectType, ReflectedRange*>* pDicCorrect = this->ParseSection(sectionName);
                if((0 != pDicCorrect) && (pDicCorrect->count() > 0))
                {
                    this->m_dicDryCorrectTable[dryItem] = pDicCorrect;
                }
            }
        }
    }

    this->CorrectColorItem();

    return (this->m_dicDryCorrectTable.count() > 0);
}

void ReflectedChecker::CorrectColorItem()
{
    if(this->m_dicDryCorrectTable.contains(Color))
    {
        QMap<eReflectType, ReflectedRange*>* pDicCorrect = this->m_dicDryCorrectTable[Color];
        for(int index = R; index <= B; ++index)
        {
            eReflectType type = (eReflectType)index;
            ReflectedRange* pRange = pDicCorrect->value(type);
            pRange->fRanges.fUplimits = this->GetColorBase(type);
            if(pRange->fRanges.fLolimits >= pRange->fRanges.fUplimits)
            {
                if(pDicCorrect->remove(type))
                {
                    delete pRange;
                    pRange = 0;
                }
            }
        }
    }
}

float ReflectedChecker::GetColorBase(eReflectType type)
{
    FilePathManager mng;
    QString userFilePath = mng.GetCurrentPresetPath() + "/Setup.ini";
    IniAccess access(userFilePath);
    QString head = "General";
    QString whiteColorRBase = access.Read(head, "WhiteColorRBase");
    QString whiteColorGBase = access.Read(head, "WhiteColorGBase");
    QString whiteColorBBase = access.Read(head, "WhiteColorBBase");

    int value = 1400;
    float fvalue = 1.0;
    bool ret = true;
    switch(type)
    {
        case R:
            value = whiteColorRBase.toInt();
            break;
        case G:
            value = whiteColorGBase.toInt();//SetupPreset::GetInstance()->GetIntData(WhiteColorGBase);
            break;
        case B:
            value = whiteColorBBase.toInt();//SetupPreset::GetInstance()->GetIntData(WhiteColorBBase);
            break;
        default:
            ret = false;
            break;
    }

    if(ret)
    {
        fvalue = (1.15f * value) / 1000;
    }

    return fvalue;
}

QMap<eReflectType, ReflectedRange *> *ReflectedChecker::ParseSection(QString sectionName)
{
    IniAccess access(this->m_path);
    QStringList keylist = access.ReadKeys(sectionName);
    QMap<eReflectType, ReflectedRange *>* pDicCorrectList = new QMap<eReflectType, ReflectedRange *>();

    for(int i = 0; i < keylist.size(); ++i)
    {
        QString key = keylist.at(i);
        if(this->m_dicColorType.contains(key))
        {
            eReflectType Type = this->m_dicColorType[key];
            QString itemValue = access.Read(sectionName, key);
            ReflectedRange* reflexRange = this->ParseRange(Type, itemValue);
            if((0 != pDicCorrectList) && (0 != reflexRange))
            {
                pDicCorrectList->insert(Type, reflexRange);
            }
        }
    }

    if((0 != pDicCorrectList) && (0 == pDicCorrectList->count()))
    {
        pDicCorrectList->clear();
        delete pDicCorrectList;
        pDicCorrectList = 0;
    }

    return pDicCorrectList;
}

ReflectedRange *ReflectedChecker::ParseRange(eReflectType type, QString content)
{
    ReflectedRange * reflexRange = 0;
    content = content.trimmed();
    if((!content.isNull()) && (!content.isEmpty()))
    {
        QString item = content.replace("[", "").replace("]","").trimmed();
        QStringList list = item.split("#");
        if(2 == list.size())
        {
            bool ret1 = false;
            bool ret2 = false;

            float flo = list.at(0).trimmed().toFloat(&ret1);
            float fup = list.at(1).trimmed().toFloat(&ret2);
            if((ret1 && ret2) && (flo < fup))
            {
                reflexRange = new ReflectedRange();
                if(0 != reflexRange)
                {
                    reflexRange->eType = type;
                    reflexRange->fRanges.fLolimits = flo;
                    reflexRange->fRanges.fUplimits = fup;
                }
            }
        }
    }

    return reflexRange;
}

const QMap<eReflectType, ReflectedRange *> *ReflectedChecker::GetCorrectMap(EnumChemistryType type)
{
    QMap<eReflectType, ReflectedRange *> *ptable = 0;
    if(this->m_dicDryCorrectTable.contains(type))
    {
        ptable = this->m_dicDryCorrectTable[type];
    }

    return ptable;
}

ReflectedChecker::ReflectState ReflectedChecker::CalcCheck(const DryColor &color, const QMap<eReflectType, ReflectedRange *> *pThreshlod)
{
    ReflectState ret = ReflectOK;
    for(int index = R; index <= B; ++index)
    {
        eReflectType type = (eReflectType)index;
        if(pThreshlod->contains(type))
        {
            const ReflectedRange *pThreadRange = pThreshlod->value(type);
            const float value = color.GetValue(type);

            if (value < pThreadRange->fRanges.fLolimits)
            {
                ret = ReflectLowOVER;
            }
            else if (value > pThreadRange->fRanges.fUplimits)
            {
                ret = ReflectUpOVER;
            }

            if(ret == ReflectLowOVER || ret == ReflectUpOVER)
            {
                QString logs = QString("\r\nSampleId = %1  ") + QString::number(type) + " " + QString::number(value) + " "
                        + QString::number(pThreadRange->fRanges.fLolimits) + " " + QString::number(pThreadRange->fRanges.fUplimits);
                //LogSystem::Instance()->Write(DryData, logs);
                break;
            }
        }
    }

    return ret;
}

ReflectedChecker::ReflectState ReflectedChecker::CalcCheckReflection(QList<ReflectionItem> list)
{
    ReflectState ret = ReflectOK;
    QList<EnumChemistryType> sortList = ParameterSystem::Instance()->GetParamSortList();

    foreach(ReflectionItem item, list)
    {
        foreach(EnumChemistryType chemistryType, sortList)
        {
            if (item.Type() == chemistryType)
            {
                QString strValue = item.Value();
                if (!strValue.isEmpty())
                {
                    QStringList valueRGBList = strValue.split(" ", QString::SkipEmptyParts);

                    const QMap<eReflectType, ReflectedRange*>* pdicMap = this->GetCorrectMap((EnumChemistryType)chemistryType);
                    for(int index = R; index <= B; ++index)
                    {
                        eReflectType type = (eReflectType)index;
                        float value = 0.0;
                        if(pdicMap->contains(type))
                        {
                            const ReflectedRange *pThreadRange = pdicMap->value(type);
                            switch (type) {
                            case R:
                                value = valueRGBList.at(0).toFloat();
                                //qDebug() << "value : " << value;
                                break;
                            case G:
                                value = valueRGBList.at(1).toFloat();
                                //qDebug() << "value : " << value;
                                break;
                            case B:
                                value = valueRGBList.at(2).toFloat();
                                //qDebug() << "value : " << value;
                                break;
                            default:
                                break;
                            }

                            //const float value = color.GetValue(type);
                            if (value < pThreadRange->fRanges.fLolimits)
                            {
                                ret = ReflectLowOVER;
                            }
                            else if (value > pThreadRange->fRanges.fUplimits)
                            {
                                ret = ReflectUpOVER;
                            }

                            if(ret == ReflectLowOVER || ret == ReflectUpOVER)
                            {
                                QString logs = QString("\r\nSampleId = %1  ") + QString::number(type) + " " + QString::number(value) + " "
                                        + QString::number(pThreadRange->fRanges.fLolimits) + " " + QString::number(pThreadRange->fRanges.fUplimits);
                                //LogSystem::Instance()->Write(DryData, logs);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return ret;
}

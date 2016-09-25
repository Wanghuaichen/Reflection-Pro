#include "StripItemProvider.h"
//#include "SetupPreset.h"
//#include "setuppreset.h"
#include "filepathmanager.h"
#include "IniAccess.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>

const QString ITEM_SECTION = "ITEM";
// 加上颜色分类
const int Item_11_Num = 11 + 1;
const int Item_12_Num = 12 + 1;
const int Item_14_Num = 14 + 1;

StripItemProvider::StripItemProvider()
{
    this->Init();
    this->LoadStripItem();
}

StripItemProvider::~StripItemProvider()
{
    this->m_dicStripItem.clear();
    this->m_dicItemfileName.clear();
    this->m_dicExamName.clear();
}

bool StripItemProvider::TryReLoadStripItem()
{
    bool ok = this->Check();
    if(!ok)
    {
        ok = this->LoadStripItem();
    }

    return ok;
}

bool StripItemProvider::LoadStripItem()
{
    bool ret = false;
    this->m_dicStripItem.clear();
    int itemcount = 0;
    //int itemcount = SetupPreset::GetInstance()->GetIntData(StripItemCount);
    if(this->m_dicItemfileName.contains(itemcount))
    {
        FilePathManager fileManager;
        QString itemfiles = fileManager.ConfigurePath() + QDir::separator() + this->m_dicItemfileName.value(itemcount);
        ret = this->Load(itemfiles);
    }

    return ret;
}

int StripItemProvider::GetItemIndex(EnumChemistryType type)
{
    int index = -1;
    if(LEU == type)
    {
        this->TryReLoadStripItem();
    }

    if(this->m_dicStripItem.contains(type))
    {
        index = this->m_dicStripItem.value(type);
    }

    return index;
}

bool StripItemProvider::GetTypeByIndex(int index, EnumChemistryType &type)
{
    bool ret = false;
    if(index >= 0 && index < this->m_dicStripItem.count())
    {
        QMap<EnumChemistryType, int>::const_iterator its;
        for(its = this->m_dicStripItem.constBegin(); its != this->m_dicStripItem.constEnd(); ++its)
        {
            if(index == its.value())
            {
                type = its.key();
                ret = true;
                break;
            }
        }
    }

    return ret;
}

quint16 StripItemProvider::CurStripItemCount() const
{
    return this->m_dicStripItem.count();
}

void StripItemProvider::Init()
{
    this->m_dicItemfileName[0] = "Dry11ItemStrip.ini";
    this->m_dicItemfileName[1] = "Dry12ItemStrip.ini";
    this->m_dicItemfileName[2] = "Dry14ItemStrip.ini";
    // 1 register Exam
    this->RegisterExamItem("LEU", LEU);
    this->RegisterExamItem("URO", URO);
    this->RegisterExamItem("MCA", MCA);
    this->RegisterExamItem("PRO", PRO);
    this->RegisterExamItem("BIL", BIL);
    this->RegisterExamItem("GLU", GLU);
    this->RegisterExamItem("VC",  VC);
    this->RegisterExamItem("SG",  SG);
    this->RegisterExamItem("KET", KET);
    this->RegisterExamItem("NIT", NIT);
    this->RegisterExamItem("CRE", CRE);
    this->RegisterExamItem("PH",  PH);
    this->RegisterExamItem("BLD", BLD);
    this->RegisterExamItem("CA",  CA);
    this->RegisterExamItem("Color", Color);
}

bool StripItemProvider::Load(QString filePathName)
{
    QFileInfo fi(filePathName);
    if(fi.isFile())
    {
        QFile file(filePathName);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QString str;
        int index = 0;
        while(!in.atEnd())
        {
            str = in.readLine().trimmed().toUpper();
            if(this->m_dicExamName.contains(str))
            {
                this->m_dicStripItem.insert(this->m_dicExamName.value(str), index);
                index++;
            }
        }

        file.close();
    }

    if(this->m_dicStripItem.count() > 0)
    {
        this->m_dicStripItem.insert(Color, (int)Color);
    }

    return (this->m_dicStripItem.count() > 0);
}

void StripItemProvider::RegisterExamItem(QString name, EnumChemistryType item)
{
    this->m_dicExamName[name] = item;
}

bool StripItemProvider::Check()
{
    bool ok = false;
    //int itemcount = SetupPreset::GetInstance()->GetIntData(StripItemCount);
    int itemcount = 0;
    int curStripItemCount = this->m_dicStripItem.count();
    switch(itemcount)
    {
        case 0:
            ok = (Item_11_Num == curStripItemCount);
            break;
        case 1:
            ok = (Item_12_Num == curStripItemCount);
            break;
        case 2:
            ok = (Item_14_Num == curStripItemCount);
            break;
        default:
            break;
    }

    return ok;
}

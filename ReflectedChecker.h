#ifndef REFLECTEDCHECKER_H
#define REFLECTEDCHECKER_H

#include <QObject>
#include <QMap>
#include "DryColorInfo.h"
#include "StripItemProvider.h"
#include "EnumChemistryType.h"
#include "DryRange.h"
#include "ReflectionItem.h"
#include "ParameterSystem.h"
class ReflectedChecker : public QObject
{
    Q_OBJECT
public:
    explicit ReflectedChecker(QObject *parent = 0);
    virtual ~ReflectedChecker();
    enum ReflectState
    {
        ReflectOK  = 0,
        ReflectNULL,
        ReflectLowOVER,
        ReflectUpOVER,
    };

signals:

public slots:
    ReflectState Check(const DryReflectedSt *dryReflect);
public:
    void Init();
    bool LoadMap();
    void CorrectColorItem();
    float GetColorBase(eReflectType type);
    QMap<eReflectType, ReflectedRange *> * ParseSection(QString sectionName);
    ReflectedRange *ParseRange(eReflectType type, QString content);

    const QMap<eReflectType, ReflectedRange *> *GetCorrectMap(EnumChemistryType type);

    ReflectedChecker::ReflectState CalcCheckReflection(QList<ReflectionItem> list);
    ReflectedChecker::ReflectState CalcCheck(const DryColor &color, const QMap<eReflectType, ReflectedRange *> *pThreshlod);
private:
    QString            m_path;
    StripItemProvider  m_stripProvider;
    QMap<EnumChemistryType, QString> m_dicExamName;
    QMap<QString, eReflectType> m_dicColorType;
    QMap<EnumChemistryType, QMap<eReflectType, ReflectedRange*>*> m_dicDryCorrectTable;
    ReflectState CheckReflectCount(int lowOverCount, int upOverCount);
    void LoadOverReflectNum();
    int m_overNumLow;
    int m_overNumUp;
};

#endif // REFLECTEDCHECKER_H

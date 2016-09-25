#ifndef QUERYCONDITION_H
#define QUERYCONDITION_H

#include <QString>
#include <QVariant>
#include <QList>

#include <QDateTime>


class ConditionItem
{
    friend class QueryCondition;
    friend class DBAccess;

public:
    ConditionItem(QString fieldName, long data);
    ConditionItem(QString fieldName, QString data);
    ConditionItem(QString fieldName, QDate data);
    ConditionItem(QString fieldName, QDateTime data);

    ConditionItem(QString fieldName, QString compareOperator, long data);
    ConditionItem(QString fieldName, QString compareOperator, QString data);
    ConditionItem(QString fieldName, QString compareOperator, QDateTime data);

private:
    QString FieldName;
    QVariant Data;
    QString CompareOperator;
    QString LogicalOperator;
};

class QueryCondition
{
public:    
    QueryCondition();

    // long, int, short
    QueryCondition(QString fieldName, long data);
    QueryCondition(QString fieldName, QString compareOperator, long data);

    // string
    QueryCondition(QString fieldName, QString data);
    QueryCondition(QString fieldName, QString compareOperator, QString data);

    // string
    QueryCondition(QString fieldName, QDateTime data);
    QueryCondition(QString fieldName, QString compareOperator, QDateTime data);

    virtual ~QueryCondition();

    void And(QString fieldName, long data);
    void And(QString fieldName, QString compareOperator, long data);

    void And(QString fieldName, QString data);
    void And(QString fieldName, QString compareOperator, QString data);

    void And(QString fieldName, QDateTime data);
    void And(QString fieldName, QString compareOperator, QDateTime data);

    void Or(QString fieldName, long data);

    void Clear();

    QList<ConditionItem> GetConditiaonList() const;

private:
    void AndExpress(ConditionItem conditionItem);
    void OrExpress(ConditionItem conditionItem);

    QList<ConditionItem> m_conditionList;
};

#endif // QUERYCONDITION_H

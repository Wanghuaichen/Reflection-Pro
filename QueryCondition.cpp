#include "QueryCondition.h"

#include <QString>
#include <QVariant>

ConditionItem::ConditionItem(QString fieldName, long data)
{
    this->FieldName = fieldName;
    this->Data = data;
    this->CompareOperator = "=";
}

ConditionItem::ConditionItem(QString fieldName, QString data)
{
    this->FieldName = fieldName;
    this->Data = "'" + data + "'";
    this->CompareOperator = "=";
}

ConditionItem::ConditionItem(QString fieldName, QDate data)
{
    this->FieldName = "strftime('%Y-%m-%d', " + fieldName + ")";
    this->Data = "strftime('%Y-%m-%d', '" + data.toString("yyyy-MM-dd") + "')";
    this->CompareOperator = "=";
}

ConditionItem::ConditionItem(QString fieldName, QDateTime data)
{
    this->FieldName = "strftime('%Y-%m-%d', " + fieldName + ")";
    this->Data = "strftime('%Y-%m-%d', '" + data.toString("yyyy-MM-dd") + "')";
    this->CompareOperator = "=";
}

ConditionItem::ConditionItem(QString fieldName, QString compareOperator, long data)
{
    this->FieldName = fieldName;
    this->Data = data;
    this->CompareOperator = compareOperator;
}

ConditionItem::ConditionItem(QString fieldName, QString compareOperator, QString data)
{
    this->FieldName = fieldName;
    this->Data = "'" + data + "'";
    this->CompareOperator = compareOperator;
}

ConditionItem::ConditionItem(QString fieldName, QString compareOperator, QDateTime data)
{
    this->FieldName = "strftime('%Y-%m-%d', " + fieldName + ")";
    this->Data = "strftime('%Y-%m-%d', '" + data.toString("yyyy-MM-dd") + "')";
    this->CompareOperator = compareOperator;
}

QueryCondition::QueryCondition()
{
}

QueryCondition::QueryCondition(QString fieldName, QString data)
{
    this->AndExpress(ConditionItem(fieldName, data));
}

QueryCondition::QueryCondition(QString fieldName, long data)
{
    this->AndExpress(ConditionItem(fieldName, data));
}

QueryCondition::QueryCondition(QString fieldName, QString compareOperator, QString data)
{
    this->AndExpress(ConditionItem(fieldName, compareOperator, data));
}

QueryCondition::QueryCondition(QString fieldName, QDateTime data)
{
    this->AndExpress(ConditionItem(fieldName, data));
}

QueryCondition::QueryCondition(QString fieldName, QString compareOperator, QDateTime data)
{
    this->AndExpress(ConditionItem(fieldName, compareOperator, data));
}

QueryCondition::QueryCondition(QString fieldName, QString compareOperator, long data)
{
    this->AndExpress(ConditionItem(fieldName, compareOperator, data));
}

QueryCondition::~QueryCondition()
{
}

void QueryCondition::And(QString fieldName, QString data)
{
    this->AndExpress(ConditionItem(fieldName, data));
}

void QueryCondition::And(QString fieldName, QString compareOperator, long data)
{
    this->AndExpress(ConditionItem(fieldName, compareOperator, data));
}

void QueryCondition::And(QString fieldName, QString compareOperator, QString data)
{
    this->AndExpress(ConditionItem(fieldName, compareOperator, data));
}

void QueryCondition::And(QString fieldName, QDateTime data)
{
    this->AndExpress(ConditionItem(fieldName, data));
}

void QueryCondition::And(QString fieldName, QString compareOperator, QDateTime data)
{
    this->AndExpress(ConditionItem(fieldName, compareOperator, data));
}

void QueryCondition::And(QString fieldName, long data)
{
    this->AndExpress(ConditionItem(fieldName, data));
}

QList<ConditionItem> QueryCondition::GetConditiaonList() const
{
    return this->m_conditionList;
}

void QueryCondition::OrExpress(ConditionItem conditionItem)
{
    conditionItem.LogicalOperator = " OR ";
    this->m_conditionList << conditionItem;
}

void QueryCondition::Or(QString fieldName, long data)
{
    this->OrExpress(ConditionItem(fieldName, data));
}

void QueryCondition::Clear()
{
    this->m_conditionList.clear();
}

void QueryCondition::AndExpress(ConditionItem conditionItem)
{
    conditionItem.LogicalOperator = " AND ";
    this->m_conditionList << conditionItem;
}

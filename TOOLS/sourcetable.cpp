#include "sourcetable.h"


SourceTable* SourceTable::instance = nullptr;

SourceTable* SourceTable::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SourceTable();
    }

    return instance;
}

SourceTable::SourceTable(QObject *parent) : QObject(parent)
{
    m_emblemTable.insert("none",":/UI/RESOURCE/test_SR_object5.png");
}

SourceTable::~SourceTable()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

QString SourceTable::findEmblemTablePath(QString name)
{
    return m_emblemTable.value(name);
}

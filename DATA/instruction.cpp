#include "instruction.h"

QMap <QString,Character*> Instruction::m_characterTable={};

Instruction::Instruction(QObject *parent) : QObject(parent)
{

}

QString Instruction::insObject() const
{
    return m_insObject;

}

void Instruction::setInsObject(const QString &object)
{
    if(m_insObject!=object)
    {
        m_insObject=object;
        emit insObjectChanged(m_insObject);
    }
}

QString Instruction::insDoing() const
{
    return m_insDoing;
}

void Instruction::setInsDoing(const QString &doing)
{
    if(m_insDoing!=doing)
    {
        m_insDoing=doing;
        emit insDoingChanged(m_insDoing);
    }
}

QString Instruction::insCategory() const
{
    return m_insCategory;
}

void Instruction::setInsCategory(const QString &category)
{
    if(m_insCategory!=category)
    {
        m_insCategory=category;
        emit insCategoryChanged(m_insCategory);
    }
}

void Instruction::addInTable(QString name, Character * Char)
{
    m_characterTable.insert("name",Char);
}

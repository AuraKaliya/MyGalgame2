#include "playerbase.h"

PlayerBase::PlayerBase()
{

}

int PlayerBase::getID() const
{
    return ID;
}

void PlayerBase::setID(int value)
{
    ID = value;
}

QString PlayerBase::getName() const
{
    return Name;
}

void PlayerBase::setName(const QString &value)
{
    Name = value;
}

int PlayerBase::getDefaultCardDeck() const
{
    return defaultCardDeckID;
}

void PlayerBase::setDefaultCardDeck(int value)
{
    defaultCardDeckID = value;
}

int PlayerBase::getDefaultHeadImageID() const
{
    return defaultHeadImageID;
}

void PlayerBase::setDefaultHeadImageID(int value)
{
    defaultHeadImageID = value;
}

QList<int> PlayerBase::getBuffList() const
{
    return buffList;
}

void PlayerBase::setBuffList(const QList<int> &value)
{
    buffList = value;
}

QMap<QString, ModelBase *> PlayerBase::getModel() const
{
    return model;
}

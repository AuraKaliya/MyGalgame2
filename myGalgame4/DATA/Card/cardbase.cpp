#include "cardbase.h"

CardBase::CardBase(QObject *parent) : QObject(parent)
{

}

int CardBase::getCardID() const
{
    return cardID;
}

void CardBase::setCardID(int value)
{
    cardID = value;
}

QString CardBase::getCardName() const
{
    return cardName;
}

void CardBase::setCardName(const QString &value)
{
    cardName = value;
}

QString CardBase::getCardMainCategory() const
{
    return cardMainCategory;
}

void CardBase::setCardMainCategory(const QString &value)
{
    cardMainCategory = value;
}

QString CardBase::getCardSecondCategory() const
{
    return cardSecondCategory;
}

void CardBase::setCardSecondCategory(const QString &value)
{
    cardSecondCategory = value;
}

QString CardBase::getCardRarity() const
{
    return cardRarity;
}

void CardBase::setCardRarity(const QString &value)
{
    cardRarity = value;
}



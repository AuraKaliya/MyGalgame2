#ifndef CARDBASE_H
#define CARDBASE_H

#include <QObject>
#include <QString>
#include <QMap>

#include "../Model/modelbase.h"

#pragma execution_character_set("utf-8")
class CardBase : public QObject
{
    Q_OBJECT
public:
    explicit CardBase(QObject *parent = nullptr);

    int getCardID() const;
    void setCardID(int value);

    QString getCardName() const;
    void setCardName(const QString &value);

    QString getCardMainCategory() const;
    void setCardMainCategory(const QString &value);

    QString getCardSecondCategory() const;
    void setCardSecondCategory(const QString &value);

    QString getCardRarity() const;
    void setCardRarity(const QString &value);

    QString getCardIntroduction() const;
    void setCardIntroduction(const QString &value);

    QString getCardImage() const;
    void setCardImage(const QString &value);

protected:
    //对于一个卡牌而言，需要有卡牌ID、Name、主类、副类、稀有度、介绍、立绘
    //卡牌需要载入model进行具体化功能。

    int cardID;
    QString cardName;
    QString cardMainCategory;
    QString cardSecondCategory;
    QString cardRarity;
    QString cardIntroduction;
    QString cardImage;

    QMap<QString,ModelBase*> model;


signals:



};

#endif // CARDBASE_H

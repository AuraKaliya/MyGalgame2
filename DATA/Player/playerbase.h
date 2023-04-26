#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include <QMap>
#include <QString>
#include <QList>


#include "../Model/modelbase.h"

#pragma execution_character_set("utf-8")
class PlayerBase
{

public:

    PlayerBase();

    int getID() const;
    void setID(int value);

    QString getName() const;
    void setName(const QString &value);

    int getDefaultCardDeck() const;
    void setDefaultCardDeck(int value);

    int getDefaultHeadImageID() const;
    void setDefaultHeadImageID(int value);

    QList<int> getBuffList() const;
    void setBuffList(const QList<int> &value);

    QMap<QString, ModelBase *> getModel() const;

protected:
    int ID;
    QString Name;
    int defaultCardDeckID;
    int defaultHeadImageID;
    QList<int> buffList;

    QMap<QString,ModelBase*> model;



};

#endif // PLAYERBASE_H

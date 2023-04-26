#ifndef CARDSEARCH_H
#define CARDSEARCH_H

#include <QVector>
#include <QStringList>

#include <QDebug>

class CardSearch {
public:
    CardSearch();

    void setData(const QVector<QStringList>& data);
    QVector<QString> syncQue(const QString& query) const;
    QVector<QString> asyncQue(const QString& query) const;
    void updateCardShowList(const QVector<QString>& IDList);

private:
    QStringList m_allCardsID;
    QVector<QStringList> m_allCardsData;
    QVector<QStringList> m_queryList;
};


#endif // CARDSEARCH_H

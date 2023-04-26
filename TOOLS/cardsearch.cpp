#include "cardsearch.h"

#include <QString>
#include <QStringList>

CardSearch::CardSearch() {}

void CardSearch::setData(const QVector<QStringList>& data) {
    m_allCardsData = data;
    m_allCardsID.clear();
    for (const auto& row : m_allCardsData) {
        m_allCardsID.append(row[0]);
    }
}

QVector<QString> CardSearch::syncQue(const QString& query) const {
    QVector<QString> result;
    for (const auto& id : m_allCardsID) {
        if (id.startsWith(query, Qt::CaseInsensitive)) {
            result.append(id);
        }
    }
    return result;
}

QVector<QString> CardSearch::asyncQue(const QString& query) const {
    QVector<QString> result;
    for (const auto& row : m_allCardsData) {
        if (row[1].contains(query, Qt::CaseInsensitive)) {
            result.append(row[0]);
        }
    }
    return result;
}

void CardSearch::updateCardShowList(const QVector<QString>& IDList) {
    m_queryList.clear();
    for (const auto& id : IDList) {
        bool ok;
        int idNum = id.toInt(&ok);
        if (!ok) {
            continue;
        }
        for (const auto& row : m_allCardsData) {
            if (row[0].toInt() == idNum) {
                m_queryList.append(row);
                break;
            }
        }
    }
}

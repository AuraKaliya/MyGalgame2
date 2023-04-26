#include "callCard.h"
#include <QtGlobal>

callCard* callCard::m_instance = nullptr; // 静态成员变量初始化

callCard::callCard(QObject *parent) : QObject(parent)
{

}

callCard* callCard::getInstance() // 获取单例对象
{
    if (m_instance == nullptr) {
        m_instance = new callCard();
    }
    return m_instance;
}

void callCard::setCardPool(const QVector<int>& cardPool)
{
    m_cardPool = cardPool;
}

void callCard::setCardRarity(const QVector<QString>& cardRarity)
{
    m_cardRarity = cardRarity;
}

void callCard::setCardID(const QVector<int>& cardID)
{
    m_cardID = cardID;
}

void callCard::initCardPool(const QVector<int>& cardID, const QVector<QString>& cardRarity)
{
    m_cardID = cardID;
    m_cardRarity = cardRarity;
    m_cardPool.clear();
    const int ssrCount = 3;
    const int srCount = 10;
    const int rCount = 30;
    for (int i = 0; i < ssrCount; i++) {
        int index = -1;
        // 随机从卡池中选择一个稀有度为 SSR 的卡牌，直到找到符合条件的为止
        while (index == -1 || m_cardRarity.at(index) != "SSR") {
            index = qrand() % m_cardPool.size();
        }
        m_cardPool.insert(index, m_cardID.at(index));
    }
    for (int i = 0; i < srCount; i++) {
        int index = -1;
        // 随机从卡池中选择一个稀有度为 SR 的卡牌，直到找到符合条件的为止
        while (index == -1 || m_cardRarity.at(index) != "SR") {
            index = qrand() % m_cardPool.size();
        }
        m_cardPool.insert(index, m_cardID.at(index));
    }
    for (int i = 0; i < rCount; i++) {
        int index = -1;
        // 随机从卡池中选择一个稀有度为 R 的卡牌，直到找到符合条件的为止
        while (index == -1 || m_cardRarity.at(index) != "R") {
            index = qrand() % m_cardPool.size();
        }
        m_cardPool.insert(index, m_cardID.at(index));
    }
}

void callCard::updateCardPool()
{
    if (!m_cardID.isEmpty()) {
        m_cardPool.clear();
        const int ssrCount = 3;
        const int srCount = 10;
        const int rCount = 30;
        for (int i = 0; i < ssrCount; i++) {
            int index = -1;
            // 随机从卡牌 ID 中选择一个稀有度为 SSR 的卡牌，直到找到符合条件的为止
            while (index == -1 || m_cardRarity.at(index) != "SSR") {
                index = qrand() % m_cardID.size();
            }
           m_cardPool.insert(index, {m_cardID.at(index)});
        }
        for (int i = 0; i < srCount; i++) {
            int index = -1;
            // 随机从卡牌 ID 中选择一个稀有度为 SR 的卡牌，直到找到符合条件的为止
            while (index == -1 || m_cardRarity.at(index) != "SR") {
                index = qrand() % m_cardID.size();
            }
           m_cardPool.insert(index, {m_cardID.at(index)});
        }
        for (int i = 0; i < rCount; i++) {
            int index = -1;
            // 随机从卡牌 ID 中选择一个稀有度为 R 的卡牌，直到找到符合条件的为止
            while (index == -1 || m_cardRarity.at(index) != "R") {
                index = qrand() % m_cardID.size();
            }
            m_cardPool.insert(index, m_cardID.at(index));
        }
    }
}

QPair<int, QString> callCard::drawCard()
{
    if (m_cardPool.isEmpty()) {
        return qMakePair(-1, QString("error"));
    }
    // 随机抽取一张卡牌
    int cardIndex = qrand() % m_cardPool.size();
    int drawnCardID = m_cardPool.takeAt(cardIndex);
    QString drawnCardRarity = m_cardRarity.at(cardIndex);

    // 下面这行代码需要添加括号将初值设定项列表括起来
  return qMakePair(drawnCardID, QString(drawnCardRarity));
}

void callCard::calling()
{
    QPair<int, QString> drawnCard = drawCard();
    if (drawnCard.first != -1) {
        emit call(drawnCard.first);
        cardRecord(drawnCard.first);
    }
}

void callCard::cardRecord(int id)
{
    QList<QString> record;
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateStr = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    record.append(QString::number(id));
    record.append(dateStr);
    m_callRecord.append(record);
}

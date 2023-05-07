#ifndef CALLCARD_H
#define CALLCARD_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QDateTime>
#include <QRandomGenerator>


class callCard : public QObject
{
    Q_OBJECT
private:
    explicit callCard(QObject *parent = nullptr);

    QVector<int> m_cardPool; // 卡池
    QVector<int> m_cardID; // 卡牌 ID
    QVector<QString> m_cardRarity; // 卡牌稀有度
    QList<QList<QString> > m_callRecord; // 抽卡记录

    QRandomGenerator randint;

    void initCardPool(const QVector<int>& cardID, const QVector<QString>& cardRarity); // 初始化卡池

public:
    static callCard* getInstance(); // 获取单例对象
    void setCardPool(const QVector<int>& cardPool); // 设置卡池
    void setCardRarity(const QVector<QString>& cardRarity); // 设置卡牌稀有度
    void setCardID(const QVector<int>& cardID); // 设置卡牌 ID
    QPair<int, QString> drawCard(); // 抽卡
    void updateCardPool(); // 更新卡池
    void calling(); // 模拟用户进行一次抽卡操作
    void cardRecord(int id); // 记录抽卡记录

signals:
    void call(int id); // 抽到卡牌时发出的信号

private:
    static callCard* m_instance; // 静态成员变量，用来保存单例对象

};

#endif // CALLCARD_H

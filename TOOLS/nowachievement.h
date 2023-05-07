#ifndef NOWACHIEVEMENT_H
#define NOWACHIEVEMENT_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QObject>

#include <QDebug>


class CharacterCard {
public:
    int ID;
    QString LoveLevel;
    QString LoveExp;
};

class NowAchievement: public QObject
{
       Q_OBJECT
public:
    static NowAchievement* getInstance();

    // 设置存档ID
    void setSaveId(int id);
    // 获取存档ID
    int getSaveId() const;

    // 设置存档创建时间
    void setCreateTime(const QString& time);
    // 获取存档创建时间
    QString getCreateTime() const;

    // 设置上一次存档时间
    void setUpdateTime(const QString& time);
    // 获取上一次存档时间
    QString getUpdateTime() const;

    // 添加卡牌信息
    void addCardInfo(const CharacterCard& cardInfo);
    // 移除卡牌信息
    void removeCardInfo(int id);
    // 获取所有卡牌信息
    QVector<CharacterCard> getCardInfos() const;

    // 设置卡组信息
    void setDeckInfo(const QVector<QVector<QString>>& info);
    // 获取卡组信息
    QVector<QVector<QString> > getDeckInfo() const;

    // 增加货币数量
    void addCurrency(const QPair<QString, int>& currency);
    // 减少货币数量
    void removeCurrency(const QPair<QString, int>& currency);
    // 获取所有货币信息
    QVector<QPair<QString, int> > getCurrencies() const;
    // 获取某个货币数量
    int getCurrencyAmount(const QString& currencyName) const;

    // 设置剧情解锁进度
    void setStoryProgress(const QVector<int>& progress);
    // 获取剧情解锁进度
    QVector<int> getStoryProgress() const;

    void updateCardInfos(const QVector<CharacterCard>& cardInfos);
    void updateDeckInfo(const QVector<QVector<QString> >& deckInfo);
    void updateCurrencies(const QVector<QPair<QString, int> >& currencies);
    void updateStoryProgress(const QVector<int>& storyProgress);


    void printMe();
private:
    NowAchievement();
    NowAchievement(const NowAchievement&) = delete;
    NowAchievement& operator=(const NowAchievement&) = delete;



private:
    static NowAchievement* instance;
    int m_saveId; // 存档ID
    QString m_createTime; // 存档创建时间
    QString m_updateTime; // 上一次存档时间
    QVector<CharacterCard> m_cardInfos; // 人物卡的信息
    QVector<QVector<QString> > m_deckInfo; // 卡组信息
    QVector<QPair<QString, int> > m_currencies; // 货币信息
    QVector<int> m_storyProgress; // 剧情解锁进度


signals:
    void cardInfosUpdated(const QVector<CharacterCard>& cardInfos);
    void deckInfoUpdated(const QVector<QVector<QString> >& deckInfo);
    void currenciesUpdated(const QVector<QPair<QString, int> >& currencies);
    void storyProgressUpdated(const QVector<int>& storyProgress);


};

#endif // NOWACHIEVEMENT_H

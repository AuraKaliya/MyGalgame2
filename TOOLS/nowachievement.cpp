#include "nowachievement.h"

NowAchievement* NowAchievement::instance = nullptr;

NowAchievement* NowAchievement::getInstance()
{
    if (!instance) {
        instance = new NowAchievement();
    }
    return instance;
}

NowAchievement::NowAchievement()
{
    m_saveId = 0;
}

void NowAchievement::setSaveId(int id)
{
    m_saveId = id;
}

int NowAchievement::getSaveId() const
{
    return m_saveId;
}

void NowAchievement::setCreateTime(const QString& time)
{
    m_createTime = time;
}

QString NowAchievement::getCreateTime() const
{
    return m_createTime;
}

void NowAchievement::setUpdateTime(const QString& time)
{
    m_updateTime = time;
}

QString NowAchievement::getUpdateTime() const
{
    return m_updateTime;
}

QVector<CharacterCard> NowAchievement::getCardInfos() const
{
    return  m_cardInfos;
}

void NowAchievement::setDeckInfo(const QVector<QVector<QString>>& info)
{
    m_deckInfo = info;
}

QVector<QVector<QString>> NowAchievement::getDeckInfo() const
{
    return m_deckInfo;
}

void NowAchievement::addCurrency(const QPair<QString, int>& currency)
{
    for (auto& item : m_currencies) {
        if (item.first == currency.first) {
            item.second += currency.second;
            return;
        }
    }

    m_currencies.append(currency);
}

void NowAchievement::removeCurrency(const QPair<QString, int>& currency)
{
    for (auto it = m_currencies.begin(); it != m_currencies.end(); ++it) {
        if (it->first == currency.first) {
            it->second -= currency.second;
            if (it->second <= 0) {
                m_currencies.erase(it);
            }
            break;
        }
    }
}

QVector<QPair<QString, int>> NowAchievement::getCurrencies() const
{
    return m_currencies;
}

int NowAchievement::getCurrencyAmount(const QString& currencyName) const
{
    for (const auto& item : m_currencies) {
        if (item.first == currencyName) {
            return item.second;
        }
    }
    return 0;
}

void NowAchievement::setStoryProgress(const QVector<int>& progress)
{
    m_storyProgress = progress;
}

QVector<int> NowAchievement::getStoryProgress() const
{
    return m_storyProgress;
}
void NowAchievement::updateCardInfos(const QVector<CharacterCard>& cardInfos)
{
    m_cardInfos = cardInfos;
    emit cardInfosUpdated(m_cardInfos);
}

// 更新卡组信息
void NowAchievement::updateDeckInfo(const QVector<QVector<QString>>& deckInfo)
{
    m_deckInfo = deckInfo;
    emit deckInfoUpdated(m_deckInfo);
}

// 更新货币信息
void NowAchievement::updateCurrencies(const QVector<QPair<QString, int> >& currencies)
{
    m_currencies = currencies;
    emit currenciesUpdated(m_currencies);
}

// 更新剧情解锁进度
void NowAchievement::updateStoryProgress(const QVector<int>& storyProgress)
{
    m_storyProgress = storyProgress;
    emit storyProgressUpdated(m_storyProgress);
}

void NowAchievement::printMe()
{
   // qDebug()<<m_saveId<<endl<<m_createTime<<" "<<m_updateTime<<endl;

           //  <<endl<<m_deckInfo<<endl<<m_currencies<<endl<<m_storyProgress<<endl;

}

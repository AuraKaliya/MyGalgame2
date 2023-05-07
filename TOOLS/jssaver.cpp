#include "jssaver.h"

QString getCurrentTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    return currentTimeStr;
}

JSSaver::JSSaver(QObject *parent) : QObject(parent)
{

}

void JSSaver::saveAchievementToJsonFile()
{
    QJsonObject jsonObj;

    // 保存存档ID等信息
    jsonObj.insert("saveId", m_achievement->getSaveId());
    jsonObj.insert("createTime", m_achievement->getCreateTime());
    jsonObj.insert("updateTime", getCurrentTime());

    // 保存人物卡信息
    QJsonArray cardInfosJsonArray;
    QVector<CharacterCard> cardInfos = m_achievement->getCardInfos();
    for (const auto& cardInfo : cardInfos) {
        QJsonObject obj;
        obj.insert("ID", cardInfo.ID);
        obj.insert("LoveLevel", cardInfo.LoveLevel);
        obj.insert("LoveExp", cardInfo.LoveExp);
        cardInfosJsonArray.append(obj);
    }
    jsonObj.insert("cardInfos", cardInfosJsonArray);
    // 保存卡组信息
    QJsonArray deckInfoJsonArray;
    QVector<QVector<QString>> deckInfo = m_achievement->getDeckInfo();
    for (const auto& deck : deckInfo) {
        QJsonArray deckArray;
        for (const auto& str : deck) {
            deckArray.append(str);
        }
        deckInfoJsonArray.append(deckArray);
    }
    jsonObj.insert("deckInfo", deckInfoJsonArray);

    // 保存货币信息
    QJsonArray currenciesJsonArray;
    QVector<QPair<QString, int>> currencies = m_achievement->getCurrencies();
    for (const auto& currency : currencies) {
        QJsonObject obj;
        obj.insert("name", currency.first);
        obj.insert("amount", currency.second);
        currenciesJsonArray.append(obj);
    }
    jsonObj.insert("currencies", currenciesJsonArray);

    // 保存剧情解锁进度
    QJsonArray storyProgressJsonArray;
    QVector<int> storyProgress = m_achievement->getStoryProgress();
    for (const auto& progress : storyProgress) {
        storyProgressJsonArray.append(progress);
    }
    jsonObj.insert("storyProgress", storyProgressJsonArray);

    QJsonDocument jsonDoc(jsonObj);
    QString jsonStr = jsonDoc.toJson();

    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 打开文件失败
        return;
    }

    QTextStream out(&file);
    out << jsonStr;

    file.close();
}
void JSSaver::init()
{

    m_achievement=NowAchievement::getInstance();

}


void JSSaver::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

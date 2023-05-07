#include "jsreader.h"

JSReader::JSReader()
{

}

void JSReader::readJsonFileToAchievement()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 打开文件失败
        return;
    }

    QString jsonStr = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        // 解析json内容失败
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    // 存档ID
    int saveId = jsonObj.value("saveId").toInt();
    m_achievement->setSaveId(saveId);

    // 存档创建时间
    QString createTime = jsonObj.value("createTime").toString();
    m_achievement->setCreateTime(createTime);

    // 上一次存档时间
    QString updateTime = jsonObj.value("updateTime").toString();
    m_achievement->setUpdateTime(updateTime);

    // 人物卡信息
    QJsonArray cardInfosJsonArray = jsonObj.value("cardInfos").toArray();
    QVector<CharacterCard> cardInfos;
    for (const auto& cardInfoJson : cardInfosJsonArray) {
        QJsonObject obj = cardInfoJson.toObject();
        int id = obj.value("ID").toInt();
        QString loveLevel = obj.value("LoveLevel").toString();
        QString loveExp = obj.value("LoveExp").toString();
        CharacterCard cardInfo = {id, loveLevel, loveExp};
        cardInfos.append(cardInfo);
    }
    m_achievement->updateCardInfos(cardInfos);

    // 卡组信息
    QJsonArray deckInfoJsonArray = jsonObj.value("deckInfo").toArray();
    QVector<QVector<QString>> deckInfo;
    for (const auto& deckJson : deckInfoJsonArray) {
        QJsonArray deckArray = deckJson.toArray();
        QVector<QString> deck;
        for (const auto& str : deckArray) {
            deck.append(str.toString());
        }
        deckInfo.append(deck);
    }
    m_achievement->updateDeckInfo(deckInfo);
    emit deckInfoUpdated(deckInfo);

    // 货币信息
    QJsonArray currenciesJsonArray = jsonObj.value("currencies").toArray();
    QVector<QPair<QString, int>> currencies;
    for (const auto& currencyJson : currenciesJsonArray) {
        QJsonObject obj = currencyJson.toObject();
        QString name = obj.value("name").toString();
        int amount = obj.value("amount").toInt();
        QPair<QString, int> currency = {name, amount};
        currencies.append(currency);
    }
    m_achievement->updateCurrencies(currencies);

    // 剧情解锁进度
    QJsonArray storyProgressJsonArray = jsonObj.value("storyProgress").toArray();
    QVector<int> storyProgress;
    for (const auto& progressJson : storyProgressJsonArray) {
        storyProgress.append(progressJson.toInt());
    }
    m_achievement->updateStoryProgress(storyProgress);

    m_achievement->printMe();
}

QVector<Character*> JSReader::readJsonFileToCharacter()
{
    QVector<Character*> characterList;

    QFile jsonFile(m_filePath);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open JSON file.";
        return characterList;
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument document(QJsonDocument::fromJson(jsonData));

    QJsonObject object = document.object();

    for (auto it = object.begin(); it != object.end(); ++it)
    {
        QJsonValue value = it.value();

        if (value.isObject())
        {
            QJsonObject jsonObject = value.toObject();

            int id = jsonObject["ID"].toInt();
            QString name = jsonObject["Name"].toString();

            QVector<QString> gesture;
            gesture.append(jsonObject["Gesture_Normal"].toString());
            gesture.append(jsonObject["Gesture_Happy"].toString());
            gesture.append(jsonObject["Gesture_Shy"].toString());
            gesture.append(jsonObject["Gesture_Lose"].toString());

            QString lines = jsonObject["Lines"].toString();
            QStringList lineList = lines.split("|");

            QVector<QString> lineVector;
            for (QString line : lineList)
            {
                lineVector.append(line);
            }

            QString introduction = jsonObject["Introduction"].toString();

            Character* newCharacter = new Character();
            newCharacter->init(id, name, gesture, lineVector, introduction);

            characterList.append(newCharacter);
        }
    }

    jsonFile.close();

    return characterList;
}

void JSReader::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

void JSReader::init()
{
    m_achievement=NowAchievement::getInstance();
    m_musicPlayer=MusicPlayer::getInstance();
}
void JSReader::readJsonFileToMusicPlayer()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 打开文件失败
        return;
    }

    QString jsonStr = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        // 解析json内容失败
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    QJsonArray musicListJsonArray = jsonObj.value("musicList").toArray();
    QVector<QPair<QString, QString>> musicList;
    for (const auto& musicJson : musicListJsonArray) {
        QJsonObject obj = musicJson.toObject();
        QString name = obj.value("name").toString();
        QString src = obj.value("src").toString();
          qDebug()<<name<<"-"<<src;
        QPair<QString, QString> music = {name, src};
        musicList.append(music);
    }
    MusicPlayer::getInstance()->init(musicList);
}

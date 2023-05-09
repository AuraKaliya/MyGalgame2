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
    m_menuWidget=MenuWidget::getInstance();
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
void JSReader::readJsonFileToStyle()
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

    // 获取/设置风格名称
    QString styleName = jsonObj.value("StyleName").toString();
    Style::getInstance()->setStyleName(styleName);

    // 获取/设置按钮样式
    QString btnStyle = jsonObj.value("BtnStyle").toString();
    Style::getInstance()->setBtnStyle(btnStyle);

    // 获取/设置主要标签颜色
    QString primaryLabelStr = jsonObj.value("PrimaryLabel").toString();
    QColor primaryLabel(primaryLabelStr);
    Style::getInstance()->setPrimaryLabel(primaryLabel);

    // 获取/设置背景颜色
    QString backgroundStr = jsonObj.value("Background").toString();
    QColor background(backgroundStr);
    Style::getInstance()->setBackground(background);

    // 获取/设置图标颜色
    QString iconStr = jsonObj.value("Icon").toString();
    QColor icon(iconStr);
    Style::getInstance()->setIcon(icon);

    // 获取/设置深色文本颜色
    QString textDeepStr = jsonObj.value("TextDeep").toString();
    QColor textDeep(textDeepStr);
    Style::getInstance()->setTextDeep(textDeep);

    // 获取/设置浅色文本颜色
    QString textShoalStr = jsonObj.value("TextShoal").toString();
    QColor textShoal(textShoalStr);
    Style::getInstance()->setTextShoal(textShoal);

    // 获取/设置高亮文本颜色
    QString textHighLightStr = jsonObj.value("TextHighLight").toString();
    QColor textHighLight(textHighLightStr);
    Style::getInstance()->setTextHighLight(textHighLight);

    // 获取/设置主标签颜色
    QString mainLabelStr = jsonObj.value("MainLabel").toString();
    QColor mainLabel(mainLabelStr);
    Style::getInstance()->setMainLabel(mainLabel);

    emit Style::getInstance()->styleChanged();
}

void JSReader::readJsonFileToMenuWidget()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    QJsonObject rootObj = jsonDoc.object();


    // 背景图片
    QString bgPath = rootObj.value("backgroundImage").toString();
    QPixmap background(bgPath);
    m_menuWidget->setBackground(background);

    // 标题
    QJsonObject titleObj = rootObj.value("title").toObject();
    QString titlePath = titleObj.value("TitleImage").toString();
    QPixmap title(titlePath);
    QString name = titleObj.value("Name").toString();
    m_menuWidget->setTitle(title, name);

    // 版本号
    QJsonObject versionObj = rootObj.value("version").toObject();
    QString version = versionObj.value("Text").toString();
    m_menuWidget->setVersion(version);

    // 跳转组件
    QVector<QJsonObject> jumpGroup;
    QJsonArray arr = rootObj.value("jumpGroup").toArray();
    foreach (const auto &v, arr) {
        QJsonObject obj = v.toObject();
        jumpGroup << obj;
    }

    m_menuWidget->clearJumpGroup();  // 清空原有跳转组件
    for (const auto &obj : jumpGroup) {
        QString text = obj.value("Text").toString();
        QPixmap* normalPix = new QPixmap(obj.value("NormalPix").toString());
        QPixmap* pressPix = new QPixmap(obj.value("PressPix").toString());
        bool isMask = obj.value("Mask").toBool();

        QSize size(obj.value("FixedSize").toArray().at(0).toInt(), obj.value("FixedSize").toArray().at(1).toInt());
        qDebug()<<size;
        QPoint move(obj.value("move").toArray().at(0).toInt(), obj.value("move").toArray().at(1).toInt());
        JumpLabel *label = new JumpLabel(m_menuWidget);
        label->setFixedSize(size);
        label->setPixmapGroup(normalPix,pressPix);
        label->move(move);
        label->setVisible(true);
        if (isMask) {
            label->setMaskStatus(isMask);
        }
        connect(label, &JumpLabel::jump,this,[=](QWidget* destination) {
            if (text == "新存档") {
                // 处理新存档的逻辑
                qDebug()<<"新存档";
            } else if (text == "读取") {
                // 处理读取的逻辑
                qDebug()<<"读取";
            } else if (text == "设置") {
                // 处理设置的逻辑
                qDebug()<<"设置";
            } else if (text == "退出") {
                // 处理退出的逻辑
                qDebug()<<"退出";
            }
        });

        Updater::getInstance()->addJumpLabel(label);
        m_menuWidget->addJumpLabel(label);
    }

}

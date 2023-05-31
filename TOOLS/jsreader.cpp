#include "jsreader.h"

QMap<QString,FUNC_Read> JSReader::m_ReadFunction=QMap<QString,FUNC_Read>();

QMap<QString,QString> JSReader::m_Property2Type=QMap<QString,QString>();
QMap<QString,UIWidget*> JSReader::m_Name2Class=QMap<QString,UIWidget*>();
QString JSReader::m_filePath=QString("");

JSReader::JSReader()
{
    m_ReadFunction.insert(QString("StoryWidget"),&JSReader::readStoryWidget);
    m_ReadFunction.insert(QString("TalkShowWidget"),&JSReader::readTalkShowWidget);
    m_ReadFunction.insert(QString("TachieLabel"),&JSReader::readTachieLabel);


    m_Property2Type.insert(QString("BackgroundPixUrl"),QString("QPixmap"));
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
QVector<Character*> JSReader::readJsonFileToCharacter() {
    QVector<Character*> characters;

    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can't open the file!" << Qt::endl;
        return characters;
    }

    QByteArray byteArray = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(byteArray));
    QJsonObject obj = doc.object();

    if (obj.contains("Character")) {
        QJsonArray characterArray = obj["Character"].toArray();
        int characterCount = characterArray.size();

        for (int i = 0; i < characterCount; i++) {
            QJsonObject characterObject = characterArray[i].toObject();

            int ID = characterObject["ID"].toInt();
            QString name = characterObject["Name"].toString();
            QString introduction = characterObject["Introduction"].toString();
            QString nicoTitle = characterObject["NicoTitle"].toString();
            QString cardPix = characterObject["CardPix"].toString();
            QString cardSmallPix=characterObject["CardSmallPix"].toString();
            QString headPix = characterObject["HeadPix"].toString();
            QString tachiePix = characterObject["TachiePix"].toString();
            QString lines = characterObject["Lines"].toString();

            QString gestureNormal = characterObject["Gesture_Normal"].toString();
            QString gestureHappy = characterObject["Gesture_Happy"].toString();
            QString gestureShy = characterObject["Gesture_Shy"].toString();
            QString gestureLose = characterObject["Gesture_Lose"].toString();
            QString gestureAnnoyed = characterObject["Gesture_Annoyed"].toString();

            QString story=characterObject["Story"].toString();
            QString storyTitle=characterObject["StoryTitle"].toString();
            qDebug()<<gestureNormal<<gestureHappy<<gestureShy<<gestureLose;
            QVector<QString> gestures;
            gestures.push_back(gestureNormal);
            gestures.push_back(gestureHappy);
            gestures.push_back(gestureShy);
            gestures.push_back(gestureLose);
            gestures.push_back(gestureAnnoyed);

            QVector<QString> characterLines;
            QStringList lineList = lines.split("|");
            for (int j = 0; j < lineList.size(); j++) {
                characterLines.push_back(lineList[j]);
            }

            Character* character = new Character();
            character->init(ID, name, gestures, characterLines, introduction);
            character->setNicoTitle(nicoTitle);
            character->setCardPixPath(cardPix);
            character->setCardSmallPixPath(cardSmallPix);
            character->setHeadPixPath(headPix);
            character->setTachiePixPath(tachiePix);
            character->setStory(story);
            character->setStoryTitle(storyTitle);
            characters.push_back(character);
        }
    }

    file.close();

    return characters;
}

void JSReader::readJsonFile()
{
    StoryShowWidgetInfo storyShowWidgetInfo;
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 打开文件失败
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError || jsonDoc.isNull() || !jsonDoc.isObject()) {
        // 解析JSON失败
        return;
    }

    const QJsonObject& jsonObj = jsonDoc.object();
    const QJsonObject& storyShowWidgetObj = jsonObj.value("StoryShowWidget").toObject();

    if(storyShowWidgetObj.contains("BackgroundPixUrl"))
    {
        qDebug()<<"contains(\"BackgroundPixUrl\")";
        const QString bkUrl=storyShowWidgetObj.value("BackgroundPixUrl").toString();
        m_carouselWidget->initBackgroundPix(bkUrl);
    }

    ChoiceWidget * tmpChoiceWidget=new ChoiceWidget();

    // 解析ChoiceWidget信息
    if (storyShowWidgetObj.contains("ChoiceWidget")) {

        ////

        tmpChoiceWidget->setParent(m_carouselWidget);
        ////

        const QJsonObject& choiceWidgetObj = storyShowWidgetObj.value("ChoiceWidget").toObject();

        storyShowWidgetInfo.choiceWidgetInfo.widgetClass = choiceWidgetObj.value("WidgetClass").toString();

        const QJsonArray& widgetRectArray = choiceWidgetObj.value("WidgetRect").toArray();
        storyShowWidgetInfo.choiceWidgetInfo.rect.left = widgetRectArray.at(0).toInt();
        storyShowWidgetInfo.choiceWidgetInfo.rect.top = widgetRectArray.at(1).toInt();
        storyShowWidgetInfo.choiceWidgetInfo.rect.width = widgetRectArray.at(2).toInt();
        storyShowWidgetInfo.choiceWidgetInfo.rect.height = widgetRectArray.at(3).toInt();

        ////
        QRect tmpRect( storyShowWidgetInfo.choiceWidgetInfo.rect.left,
                       storyShowWidgetInfo.choiceWidgetInfo.rect.top,
                       storyShowWidgetInfo.choiceWidgetInfo.rect.width,
                       storyShowWidgetInfo.choiceWidgetInfo.rect.height);
        ////

        const QJsonObject& widgetSettingObj = choiceWidgetObj.value("WidgetSetting").toObject();
        const QJsonArray& labelArray = widgetSettingObj.value("Label").toArray();

        for (const auto& labelValue : labelArray) {
            if (labelValue.isObject()) {
                const QJsonObject& labelObj = labelValue.toObject();
                const QString& labelName = labelObj.value("LabelName").toString();
                storyShowWidgetInfo.choiceWidgetInfo.setting.labelNames << labelName;

                LabelInfo labelInfo;
                labelInfo.labelName = labelName;
                labelInfo.labelClass = labelObj.value("LabelClass").toString();

                const QJsonArray& labelGroupArray = labelObj.value("LabelGroup").toArray();
                for (const auto& groupValue : labelGroupArray) {
                    if (groupValue.isObject()) {
                        const QJsonObject& groupObj = groupValue.toObject();
                        LabelGroup labelGroup;
                        labelGroup.text = groupObj.value("Text").toString();
                        labelGroup.pix.pixUrl = groupObj.value("PixUrl").toString();
                        labelGroup.pix.status1 = groupObj.value("NormalPixUrl").toString();
                        labelGroup.pix.status2 = groupObj.value("PressPixUrl").toString();
                        labelGroup.pix.status3 = groupObj.value("ChoicePixUrl").toString();
                        const QJsonArray& rectArray = groupObj.value("Rect").toArray();
                        labelGroup.rect.left = rectArray.at(0).toInt();
                        labelGroup.rect.top = rectArray.at(1).toInt();
                        labelGroup.rect.width = rectArray.at(2).toInt();
                        labelGroup.rect.height = rectArray.at(3).toInt();



                        labelGroup.mask = groupObj.value("Mask").toBool();
                        labelGroup.cardId = groupObj.value("CardID").toInt();
                        labelGroup.destination = groupObj.value("Destination").toString();
                        labelInfo.labelGroups << labelGroup;
                    }
                }
                labelInfo.labelLayout=labelObj.value("Layout").toString();
                labelInfo.spaceH=labelObj.value("SpaceH").toInt();
                labelInfo.spaceV=labelObj.value("SpaceV").toInt();
                const QJsonArray& rectArray = labelObj.value("FirstRect").toArray();
                labelInfo.rect.left=rectArray.at(0).toInt();
                labelInfo.rect.top=rectArray.at(1).toInt();
                labelInfo.rect.width=rectArray.at(2).toInt();
                labelInfo.rect.height=rectArray.at(3).toInt();

                ////////                可用策略模式进行优化，在外部用Map连接QString和（*func）（） 调用即可                      ////////
                // TODO：根据需求将Label信息存储到数据对象中

                if( labelInfo.labelName=="TitleLabel")
                {
                    QLabel * titleLabel=new QLabel(tmpChoiceWidget);
                    titleLabel->setText(labelInfo.labelGroups[0].text);

                    QRect tmpRect(labelInfo.labelGroups[0].rect.left ,labelInfo.labelGroups[0].rect.top,
                                  labelInfo.labelGroups[0].rect.width,labelInfo.labelGroups[0].rect.height);


                    Style::getInstance()->setLabelStyleByPalete_45_white(titleLabel);
                    tmpChoiceWidget->initTitleLabel(titleLabel,tmpRect);
                }
                else if(labelInfo.labelName=="ChoiceLabel")
                {
                    QVector <JumpLabel* > jmpGroup;
                    QVector <QRect> rectGroup;
                    for (int i=0;i<labelInfo.labelGroups.size();++i)
                    {
                        JumpLabel * choiceLabel=new JumpLabel(tmpChoiceWidget);
                        choiceLabel->setText(labelInfo.labelGroups[i].text);

                        choiceLabel->setPixmapPathGroup(labelInfo.labelGroups[i].pix.status1,labelInfo.labelGroups[i].pix.status2);

                         QRect tmpRect(labelInfo.labelGroups[i].rect.left ,labelInfo.labelGroups[i].rect.top,
                                      labelInfo.labelGroups[i].rect.width,labelInfo.labelGroups[i].rect.height);
                        choiceLabel->setGeometry(tmpRect);
                        choiceLabel->setCardID(labelInfo.labelGroups[i].cardId);

                        jmpGroup<<choiceLabel;
                        rectGroup<<tmpRect;

                        Style::getInstance()->setLabelStyleByPalete_25_white(choiceLabel);

                        connect( choiceLabel,&JumpLabel::choiceCard,m_carouselWidget,&CarouselWidget::characterChoiced);
                    }

                    tmpChoiceWidget->setCurrentLabelPixPath(labelInfo.labelGroups[0].pix.status3);
                    tmpChoiceWidget->initChoiceLabel(jmpGroup,rectGroup);

                }else if(labelInfo.labelName=="SlipLabel")
                {
                    QLabel * slipLabel=new QLabel(tmpChoiceWidget);
                    slipLabel->setStyleSheet("border-image:url("+labelInfo.labelGroups[0].pix.pixUrl+")");

                    QRect tmpRect(labelInfo.labelGroups[0].rect.left ,labelInfo.labelGroups[0].rect.top,
                                  labelInfo.labelGroups[0].rect.width,labelInfo.labelGroups[0].rect.height);

                    tmpChoiceWidget->initSlipLabel(slipLabel,tmpRect);
                }
            }
        }
          //qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~555";
        m_carouselWidget->initChoiceWidget(tmpChoiceWidget,tmpRect);
          //qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~2";
    }

    CarouselMapWidget* tmpCarouselMapWidget=new CarouselMapWidget();
    // 解析CarouselMapWidget信息
    if (storyShowWidgetObj.contains("CarousMapWidget")) {




        tmpCarouselMapWidget->setParent(m_carouselWidget);

        const QJsonObject& carousMapWidgetObj = storyShowWidgetObj.value("CarousMapWidget").toObject();

        storyShowWidgetInfo.carousMapWidgetInfo.widgetClass = carousMapWidgetObj.value("WidgetClass").toString();

        const QJsonArray& widgetRectArray = carousMapWidgetObj.value("WidgetRect").toArray();
        storyShowWidgetInfo.carousMapWidgetInfo.rect.left = widgetRectArray.at(0).toInt();
        storyShowWidgetInfo.carousMapWidgetInfo.rect.top = widgetRectArray.at(1).toInt();
        storyShowWidgetInfo.carousMapWidgetInfo.rect.width = widgetRectArray.at(2).toInt();
        storyShowWidgetInfo.carousMapWidgetInfo.rect.height = widgetRectArray.at(3).toInt();

        QRect tmpRect(storyShowWidgetInfo.carousMapWidgetInfo.rect.left,
                      storyShowWidgetInfo.carousMapWidgetInfo.rect.top,
                      storyShowWidgetInfo.carousMapWidgetInfo.rect.width,
                      storyShowWidgetInfo.carousMapWidgetInfo.rect.height);

        const QJsonObject& widgetSettingObj = carousMapWidgetObj.value("WidgetSetting").toObject();
        const QJsonArray& labelArray = widgetSettingObj.value("Label").toArray();

        for (const auto& labelValue : labelArray) {
            if (labelValue.isObject()) {
                const QJsonObject& labelObj = labelValue.toObject();
                const QString& labelName = labelObj.value("LabelName").toString();
                storyShowWidgetInfo.carousMapWidgetInfo.setting.labelNames << labelName;

                LabelInfo labelInfo;
                labelInfo.labelName = labelName;
                labelInfo.labelClass = labelObj.value("LabelClass").toString();

                const QJsonArray& labelGroupArray = labelObj.value("LabelGroup").toArray();
                for (const auto& groupValue : labelGroupArray) {
                    if (groupValue.isObject()) {
                        const QJsonObject& groupObj = groupValue.toObject();
                        LabelGroup labelGroup;
                        labelGroup.mask = groupObj.value("Mask").toBool();
                        labelGroup.cardId = groupObj.value("CardID").toInt();
                        labelGroup.destination = groupObj.value("Destination").toString();
                        labelInfo.labelGroups << labelGroup;
                    }
                }

                // TODO：根据需求将Label信息存储到数据对象中
                 ////////                可用策略模式进行优化，在外部用Map连接QString和（*func）（） 调用即可                      ////////
                if(labelInfo.labelName=="ScrollerLabel")
                {

                }

            }
        }

        const QJsonObject& buttonObj = widgetSettingObj.value("Button").toObject();
        const QString& buttonName = buttonObj.value("ButtonName").toString();
        storyShowWidgetInfo.carousMapWidgetInfo.setting.buttonNames << buttonName;

        ButtonInfo buttonInfo;
        buttonInfo.buttonName = buttonName;
        buttonInfo.buttonClass = buttonObj.value("ButtonClass").toString();

        const QJsonArray& buttonGroupArray = buttonObj.value("ButtonGroup").toArray();
        for (const auto& groupValue : buttonGroupArray) {
            if (groupValue.isObject()) {
                const QJsonObject& groupObj = groupValue.toObject();
                ButtonGroup buttonGroup;
                buttonGroup.pressPix.pixUrl = groupObj.value("PressPixUrl").toString();
                buttonGroup.pressPix.status1 = groupObj.value("Status1").toString();
                buttonGroup.pressPix.status2 = groupObj.value("Status2").toString();
                buttonGroup.pressPix.status3 = groupObj.value("Status3").toString();
                buttonGroup.normalPix.pixUrl = groupObj.value("NormalPixUrl").toString();
                buttonGroup.normalPix.status1 = groupObj.value("Status1").toString();
                buttonGroup.normalPix.status2 = groupObj.value("Status2").toString();
                buttonGroup.normalPix.status3 = groupObj.value("Status3").toString();
                const QJsonArray& rectArray = groupObj.value("Rect").toArray();
                buttonGroup.rect.left = rectArray.at(0).toInt();
                buttonGroup.rect.top = rectArray.at(1).toInt();
                buttonGroup.rect.width = rectArray.at(2).toInt();
                buttonGroup.rect.height = rectArray.at(3).toInt();
                buttonGroup.link = groupObj.value("Link").toString();
                buttonInfo.buttonGroups << buttonGroup;
            }
        }

        // TODO：根据需求将Button信息存储到数据对象中
        tmpCarouselMapWidget->initChangeBtn(buttonInfo.buttonGroups[0].normalPix.pixUrl,buttonInfo.buttonGroups[1].normalPix.pixUrl);


        m_carouselWidget->initCaroselMapWidget(tmpCarouselMapWidget,tmpRect);
    }

    StoryInfoWidget * tmpStoryInfoWidget=new StoryInfoWidget();
    // 解析StoryInfoWidget信息
    if (storyShowWidgetObj.contains("StroyInfoWidget")) {

        tmpStoryInfoWidget->setParent(m_carouselWidget);

        const QJsonObject& storyInfoWidgetObj = storyShowWidgetObj.value("StroyInfoWidget").toObject();

        storyShowWidgetInfo.storyInfoWidgetInfo.widgetClass = storyInfoWidgetObj.value("WidgetClass").toString();

        const QJsonArray& widgetRectArray = storyInfoWidgetObj.value("WidgetRect").toArray();
        storyShowWidgetInfo.storyInfoWidgetInfo.rect.left = widgetRectArray.at(0).toInt();
        storyShowWidgetInfo.storyInfoWidgetInfo.rect.top = widgetRectArray.at(1).toInt();
        storyShowWidgetInfo.storyInfoWidgetInfo.rect.width = widgetRectArray.at(2).toInt();
        storyShowWidgetInfo.storyInfoWidgetInfo.rect.height = widgetRectArray.at(3).toInt();

        QRect tmpRect(storyShowWidgetInfo.storyInfoWidgetInfo.rect.left,
                      storyShowWidgetInfo.storyInfoWidgetInfo.rect.top,
                      storyShowWidgetInfo.storyInfoWidgetInfo.rect.width,
                      storyShowWidgetInfo.storyInfoWidgetInfo.rect.height);

        const QJsonObject& widgetSettingObj = storyInfoWidgetObj.value("WidgetSetting").toObject();
        const QJsonArray& linkObjectsArray = widgetSettingObj.value("LinkObjects").toArray();
        QStringList linkObjectsList;
        for (int i = 0; i < linkObjectsArray.size(); ++i) {
            linkObjectsList.append(linkObjectsArray.at(i).toString());
        }
        const QJsonArray& linkSignalsArray = widgetSettingObj.value("LinkSignals").toArray();
        QStringList linkSignalsList;
        for (int i = 0; i < linkSignalsArray.size(); ++i) {
            linkSignalsList.append(linkSignalsArray.at(i).toString());
        }
        const QJsonArray& linkSlotsArray = widgetSettingObj.value("LinkSlots").toArray();
        QStringList linkSlotsList;
        for (int i = 0; i < linkSlotsArray.size(); ++i) {
            linkSlotsList.append(linkSlotsArray.at(i).toString());
        }

        if (!linkObjectsList.isEmpty() && !linkSignalsList.isEmpty() && !linkSlotsList.isEmpty()) {
            storyShowWidgetInfo.storyInfoWidgetInfo.link.linkObjectName = linkObjectsList.first();
            storyShowWidgetInfo.storyInfoWidgetInfo.link.linkSignalName = linkSignalsList.first();
            storyShowWidgetInfo.storyInfoWidgetInfo.link.linkSlotName = linkSlotsList.first();
        }

        const QJsonObject& labelObj = widgetSettingObj.value("Label").toObject();
        const QString& labelName = labelObj.value("LabelName").toString();
        storyShowWidgetInfo.storyInfoWidgetInfo.setting.labelNames << labelName;

        LabelInfo labelInfo;
        labelInfo.labelName = labelName;
        labelInfo.labelClass = labelObj.value("LabelClass").toString();

        const QJsonArray& labelGroupArray = labelObj.value("LabelGroup").toArray();
        for (const auto& groupValue : labelGroupArray) {
            if (groupValue.isObject()) {
                const QJsonObject& groupObj = groupValue.toObject();
                LabelGroup labelGroup;
                labelGroup.text = groupObj.value("Text").toString();
                labelGroup.pix.pixUrl = groupObj.value("PixUrl").toString();
                labelGroup.pix.status1 = groupObj.value("Status1").toString();
                labelGroup.pix.status2 = groupObj.value("Status2").toString();
                labelGroup.pix.status3 = groupObj.value("Status3").toString();
                const QJsonArray& rectArray = groupObj.value("Rect").toArray();
                labelGroup.rect.left = rectArray.at(0).toInt();
                labelGroup.rect.top = rectArray.at(1).toInt();
                labelGroup.rect.width = rectArray.at(2).toInt();
                labelGroup.rect.height = rectArray.at(3).toInt();
                labelGroup.mask = groupObj.value("Mask").toBool();
                labelGroup.cardId = groupObj.value("CardID").toInt();
                labelGroup.destination = groupObj.value("Destination").toString();
                labelInfo.labelGroups << labelGroup;
            }
        }

        // TODO：根据需求将Label信息存储到数据对象中


        m_carouselWidget->initStoryInfoWidget(tmpStoryInfoWidget,tmpRect);

    }

   // connect()


    m_carouselWidget->initChoiced();
     qDebug()<<"谢谢谢谢谢谢"<<Qt::endl;
     qDebug()<<"谢谢谢谢谢谢2"<<Qt::endl;
    Style::getInstance()->setWidgetBackground(tmpStoryInfoWidget,2);
    Style::getInstance()->setWidgetBackground(tmpChoiceWidget,2);
    Style::getInstance()->setWidgetBackground(tmpCarouselMapWidget,2);
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
    m_settingWidget=SettingWidget::getInstance();
    m_rsWidget=RSWidget::getInstance();
    m_sourceTable=SourceTable::getInstance();
    m_mainWidget=MainWidget::getInstance();
    m_characterHub=CharacterHub::getInstance();
    m_characterWidget=CharacterWidget::getInstance();
    m_carouselWidget=CarouselWidget::getInstance();
    m_storyWidget=StoryWidget::getInstance();

    m_Name2Class.insert(QString("StoryWidget"),StoryWidget::getInstance());







}

void JSReader::read()
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
    readObject(reinterpret_cast<UIWidget*>(Updater::getInstance()->findParent(StoryWidget::getInstance())),jsonObj);
}

void JSReader::readObject(UIWidget *parent, const QJsonObject &obj)
{

    for(auto it=obj.begin();it!=obj.end();++it)
    {
        m_ReadFunction.value(it.value().toObject().value("Class").toString())(parent,it.value().toObject());
    }
}

void JSReader::readObject(QWidget *parent, const QJsonObject &obj)
{
    for(auto it=obj.begin();it!=obj.end();++it)
    {
        m_ReadFunction.value(it.value().toObject().value("Class").toString())(reinterpret_cast<UIWidget*>(parent),it.value().toObject());
    }
}

void JSReader::initObject(UIWidget *w, const QJsonObject &obj)
{
    //initRect
    if(obj.contains("Rect"))
    {
        readRect(w,obj);
    }

    //initSetting
    if(obj.contains("Setting"))
    {
        QJsonObject setting=obj.value("Setting").toObject();
        readSetting(w,setting);
    }
    //initContains
    if(obj.contains("Contains"))
    {
        QJsonObject childObj=obj.value("Contains").toObject();
        readObject(w,childObj);
    }
}



int JSReader::readInt(const QJsonObject &obj, const QString &key)
{
    return obj.value(key).toInt();
}

QString JSReader::readString(const QJsonObject &obj, const QString &key)
{
    return obj.value(key).toString();
}

void JSReader::readRect(UIWidget *w, const QJsonObject &obj)
{
    QJsonArray rectArray = obj.value("Rect").toArray();
    int x = rectArray.at(0).toInt();
    int y = rectArray.at(1).toInt();
    int with = rectArray.at(2).toInt();
    int height = rectArray.at(3).toInt();
    w->setGeometry(QRect(x, y, with, height));
}



QObject* JSReader::readBackgroundPix(const QJsonObject &obj)
{
    return  (QObject*)new QPixmap(obj.value("BackgroundPixUrl").toString());
}

void JSReader::readSetting(UIWidget *w, const QJsonObject &obj)
{
    if(obj.contains("BackgroundPixUrl"))
    {
        w->setBackgroundPixUrl(obj.value("BackgroundPixUrl").toString());
    }
    if(obj.contains("BackgroundMusicUrl"))
    {
        w->setBackgroundMusicUrl(obj.value("BackgroundMusicUrl").toString());
    }
    if(obj.contains("Style"))
    {
        w->setStyle(obj.value("Style").toString());
    }
}

 void JSReader::readStoryWidget( UIWidget* parent, const QJsonObject &obj)
{
    StoryWidget::getInstance()->setParent((QWidget*)parent);
//    //initRect
//    if(obj.contains("Rect"))
//    {
//        readRect(StoryWidget::getInstance(),obj);
//    }

//    //initSetting
//    if(obj.contains("Setting"))
//    {
//        QJsonObject setting=obj.value("Setting").toObject();
//        readSetting(StoryWidget::getInstance(),setting);
//    }
//    //initContains
//    if(obj.contains("Contains"))
//    {
//        QJsonObject childObj=obj.value("Contains").toObject();
//        readObject(StoryWidget::getInstance(),childObj);
//    }
    initObject(StoryWidget::getInstance(),obj);

}

void JSReader::readTalkShowWidget(UIWidget *parent, const QJsonObject &obj)
{
    TalkShowWidget * tmpTalk=new TalkShowWidget(parent);
    initObject(tmpTalk,obj);
    parent->initTalkShowWidget(tmpTalk,tmpTalk->geometry());

}

void JSReader::readTachieLabel(UIWidget *parent, const QJsonObject &obj)
{
        // 暂时用固定法  --storyShowWidget的tachieLabel
    TachieLabel * tmp=new TachieLabel(parent);
    //或许能用addWidget进行代替----主体窗体中主动调用setParent和init函数， 整个addWidget放在虚函数中 在读入处仅调用parent的addWidget
    QJsonArray rectArray = obj.value("Rect").toArray();
    int x = rectArray.at(0).toInt();
    int y = rectArray.at(1).toInt();
    int width = rectArray.at(2).toInt();
    int height = rectArray.at(3).toInt();
    tmp->setGeometry(QRect(x,y,width,height));
    tmp->initCharacter(CharacterHub::getInstance()->findCharacter(obj.value("Setting").toObject().value("DefaultCharacter").toString()),tmp->geometry());
    parent->initTachieLabel(tmp,tmp->geometry());
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
         // qDebug()<<name<<"-"<<src;
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
        qDebug()<<"No";
        return;
    }

    QString jsonStr = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        // 解析json内容失败
         qDebug()<<"No!!!!";
        return;
    }

    QMap<QString,QString> styleDic;
    QJsonObject jsonObj = jsonDoc.object();

    // 获取/设置风格名称
    QString styleName = jsonObj.value("StyleName").toString();
    styleDic.insert("StyleName",styleName);

    styleDic.insert("background_image0", " ");

    // 获取/设置背景图片1
    QString bgImage1 = jsonObj.value("background_image1").toString();
    styleDic.insert("background_image1", bgImage1);

    // 获取/设置背景图片2
    QString bgImage2 = jsonObj.value("background_image2").toString();
    styleDic.insert("background_image2", bgImage2);

    // 获取/设置背景图片3
    QString bgImage3 = jsonObj.value("background_image3").toString();
    styleDic.insert("background_image3", bgImage3);

    // 获取/设置背景图片4
    QString bgImage4 = jsonObj.value("background_image4").toString();
    styleDic.insert("background_image4", bgImage4);

    // 获取/设置标签边框样式
    QString labelBorderStyle = jsonObj.value("Label_border_style").toString();
    styleDic.insert("Label_border_style", labelBorderStyle);

    // 获取/设置标签边框半径
    QString labelBorderRadius = jsonObj.value("Label_border_radius").toString();
    styleDic.insert("Label_border_radius", labelBorderRadius);

    styleDic.insert("Label_text_style0", " ");

    for(int i=0;i<20;++i)
    {
        QString labelTextStyle=jsonObj.value("Label_text_style"+QString::number(i)).toString();
        styleDic.insert("Label_text_style"+QString::number(i), labelTextStyle);
    }
//    // 获取/设置标签文本样式1
//    QString labelTextStyle1 = jsonObj.value("Label_text_style1").toString();
//    styleDic.insert("Label_text_style1", labelTextStyle1);

//    // 获取/设置标签文本样式2
//    QString labelTextStyle2 = jsonObj.value("Label_text_style2").toString();
//    styleDic.insert("Label_text_style2", labelTextStyle2);

//    // 获取/设置标签文本样式3
//    QString labelTextStyle3 = jsonObj.value("Label_text_style3").toString();
//    styleDic.insert("Label_text_style3", labelTextStyle3);

    //qDebug()<<styleDic;
    // 将样式字典传递给Style类实例，并让它处理样式信息
    Style::getInstance()->reset(styleDic);
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
    QPoint move(titleObj.value("move").toArray().at(0).toInt(), titleObj.value("move").toArray().at(1).toInt());
    m_menuWidget->setTitle(title, name,move);

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
        //qDebug()<<size;
        QPoint move(obj.value("move").toArray().at(0).toInt(), obj.value("move").toArray().at(1).toInt());
        JumpLabel *label = new JumpLabel(m_menuWidget);
        label->setFixedSize(size);

        //______________________可放进JSON中____________________________________\\
        //
        label->setFont(QFont("楷体",45,QFont::Bold,Qt::white));
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
        label->setPalette(pa);
        label->setScaledContents(true);
        label->setPixmapPathGroup(obj.value("NormalPix").toString(),obj.value("PressPix").toString());
        label->setAlignment(Qt::AlignCenter);
        label->setText(text);
        //______________________可放进JSON中____________________________________\\
        //
        label->setPixmapGroup(normalPix,pressPix);
        label->move(move);
        label->setVisible(true);
        if (isMask) {
            label->setMaskStatus(isMask);
        }

        label->setDestination(Updater::getInstance()->findWidget(text));

        connect(label, SIGNAL(jump(QWidget*)),
                Updater::getInstance()->findParent(Updater::getInstance()->findWidget(text)),SLOT(setCurrentWidget(QWidget*)));

        Updater::getInstance()->addJumpLabel(label);
        m_menuWidget->addJumpLabel(label);

    }

}

void JSReader::readJsonFileToSetting() {
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can not open file: " << m_filePath;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qDebug() << "Failed to create JSON doc.";
        return;
    }

    QJsonObject obj = doc.object();

    // 获取标题
    QString title1 = obj.value("title1").toString();
    QString title2 = obj.value("title2").toString();

    //获取组件图
    QString settingNamePix=obj.value("obj_settingName").toString();
    QString settingValuePix=obj.value("obj_settingValue").toString();

    QString settingOptionPix=obj.value("obj_Option").toString();
    QString settingChoicePix=obj.value("obj_Choice").toString();


    // 获取背景图片
    QString backgroundImage = obj.value("backgroundImage").toString();
    m_settingWidget->setBackground(backgroundImage);


    // 获取选项卡内容
    QJsonArray widgetGroup = obj.value("WidgetGroup").toArray();
    QVector<QWidget*> widgetContents;
    int obj_x=100;
    for (int i = 0; i < widgetGroup.size(); ++i) {
        QJsonObject widgetObj = widgetGroup[i].toObject();

        QWidget* content=new QWidget();
        QString name = widgetObj.value("WidgetName").toString();

        m_settingWidget->registL2W(name,content);

        int count=0;  //用于记录已加入组件数
        // 处理Slider
        QJsonArray sliderArray = widgetObj.value("Slider").toArray();
        for (int j = 0; j < sliderArray.size(); ++j) {
            QJsonObject sliderObj = sliderArray[j].toObject();

            QString name = sliderObj.value("Name").toString();
            int defaultValue = sliderObj.value("Default").toInt();
            int minValue = sliderObj.value("MinValue").toInt();
            int maxValue = sliderObj.value("MaxValue").toInt();

                //设置的值的组件
            QLabel *tmpLabel2=new QLabel(content);
            tmpLabel2->setMask(QPixmap(settingValuePix).mask());
            tmpLabel2->setFixedSize(700,150);
            tmpLabel2->setScaledContents(true);
            tmpLabel2->setStyleSheet("border-image:url("+settingValuePix+");");
            tmpLabel2->move(obj_x+150,count*220+32);
            tmpLabel2->setVisible(true);

            //设置的名字的组件
            QLabel *tmpLabel= new QLabel(content);
            tmpLabel->setFont(QFont("楷体",20,QFont::Bold,Qt::blue));
            QPalette pal;
            pal.setColor(QPalette::WindowText,Qt::blue);
            tmpLabel->setPalette(pal);
            tmpLabel->setAlignment(Qt::AlignCenter);
            tmpLabel->setText("        "+name);
            tmpLabel->setMask(QPixmap(settingNamePix).mask());
            tmpLabel->setFixedSize(400,150);
            tmpLabel->setStyleSheet("border-image:url("+settingNamePix+");");
            tmpLabel->move(obj_x,count*220+25);
            tmpLabel->setVisible(true);



            QSlider *slider= new QSlider(content);
            slider->setFixedSize(300,100);
            slider->setMinimum(minValue);
            slider->setMaximum(maxValue);
            slider->setValue(defaultValue);
            slider->move(obj_x+420,count*220+50);
            slider->setOrientation(Qt::Horizontal);
            slider->setVisible(true);

            QLabel *tmpLabel3=new QLabel(content);
            tmpLabel3->setFixedSize(150,100);
            tmpLabel3->setFont(QFont("楷体",20,QFont::Bold,Qt::blue));
            QPalette pa;
            pa.setColor(QPalette::WindowText,Qt::blue);
            tmpLabel3->setPalette(pa);
            tmpLabel3->setScaledContents(true);
            tmpLabel3->setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency.png);");
            tmpLabel3->setAlignment(Qt::AlignCenter);
            tmpLabel3->move(obj_x+730,count*220+50);

            ++count;
        }

        // 处理Choice
        QJsonArray choiceArray = widgetObj.value("Choice").toArray();
        for (int j = 0; j < choiceArray.size(); ++j) {
            QJsonObject choiceObj = choiceArray[j].toObject();

            QString name = choiceObj.value("Name").toString();


            //设置的值的组件
            QLabel *tmpLabel2=new QLabel(content);
            tmpLabel2->setMask(QPixmap(settingValuePix).mask());
            tmpLabel2->setFixedSize(700,150);
            tmpLabel2->setScaledContents(true);
            tmpLabel2->setStyleSheet("border-image:url("+settingValuePix+");");
            tmpLabel2->move(obj_x+150,count*220+32);
            tmpLabel2->setVisible(true);


            //设置的名字的组件
            QLabel *tmpLabel= new QLabel(content);
            tmpLabel->setFont(QFont("楷体",20,QFont::Bold,Qt::blue));
            QPalette pal;
            pal.setColor(QPalette::WindowText,Qt::blue);
            tmpLabel->setPalette(pal);
            tmpLabel->setAlignment(Qt::AlignCenter);
            tmpLabel->setText("        "+name);
            tmpLabel->setMask(QPixmap(settingNamePix).mask());
            tmpLabel->setFixedSize(400,150);
            tmpLabel->setStyleSheet("border-image:url("+settingNamePix+");");
            tmpLabel->move(obj_x+0,count*220+25);

            tmpLabel->setVisible(true);





            int defaultValue = choiceObj.value("Default").toInt();
            QJsonArray valuesArray = choiceObj.value("Values").toArray();

            for (int k = 0; k < valuesArray.size(); ++k) {
                QString values=valuesArray[k].toString();
                //设置的选项的组件
                QLabel *tmpLabel3=new QLabel(content);

                tmpLabel3->setFixedSize(170,110);


                tmpLabel3->setFont(QFont("楷体",20,QFont::Bold,Qt::green));
                QPalette pal;
                pal.setColor(QPalette::WindowText,Qt::green);
                tmpLabel3->setPalette(pal);
                tmpLabel3->setAlignment(Qt::AlignCenter);
                tmpLabel3->setText(values);
                tmpLabel3->setScaledContents(true);
                tmpLabel3->setStyleSheet("border-image:url("+settingOptionPix+");");

                tmpLabel3->move(obj_x+420+k*200,count*220+50);
            }
                //设置的现选项的组件
            QLabel *tmpLabel4 =new QLabel(content);

            tmpLabel4->setScaledContents(true);
            tmpLabel4->setStyleSheet("border-image:url("+settingChoicePix+");");
            tmpLabel4->setFixedSize(190,130);
            tmpLabel4->move(obj_x+420+defaultValue*180-10,count*220+50-10);

            ++count;
        }
        content->resize(1200,count*220+350);
        widgetContents.push_back(content);
    }

    m_settingWidget->initSettingShowWidget(title1,widgetContents);

    // 获取其他图片资源
    QString choiceIcon = obj.value("choiceIcon").toString();
    QPixmap * choiceICON=new QPixmap(choiceIcon);
    QString choicedLabel = obj.value("choicedLabel").toString();
    m_settingWidget->setNowLabelPix(choicedLabel);


    // 获取选项卡标签
    QJsonArray choiceWidgetLabelGroup = obj.value("ChoiceWidgetLabelGroup").toArray();
    QVector<JumpLabel*> choiceLabels;
    for (int i = 0; i < choiceWidgetLabelGroup.size(); ++i) {
        QJsonObject labelObj = choiceWidgetLabelGroup[i].toObject();
        JumpLabel* label=new JumpLabel();
        QString text = labelObj.value("Text").toString();

        QString normalPath = labelObj.value("NormalPix").toString();
        QString pressPath = labelObj.value("PressPix").toString();
        QPixmap * normalPix= new QPixmap(normalPath);
        QPixmap *  pressPix= new QPixmap( pressPath);
        bool mask = labelObj.value("Mask").toBool();
        QJsonArray size = labelObj.value("FixedSize").toArray();
        if (size.size() == 2) {
            QSize Size(size[0].toInt(), size[1].toInt());
            label->setFixedSize(Size);
        }


        //______________________可放进JSON中____________________________________\\
        //
        label->setFont(QFont("楷体",25,QFont::Bold,Qt::blue));
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::blue);
        label->setPalette(pa);
        label->setScaledContents(true);
        label->setPixmapPathGroup(normalPath,pressPath);
        label->setPixmapGroup(normalPix,pressPix);
        label->setAlignment(Qt::AlignCenter);
        label->setText(text);
        //______________________可放进JSON中____________________________________\\
        //
        label->setPixmapGroup(normalPix,pressPix);
        label->setVisible(true);
        if (mask) {
            label->setMaskStatus(mask);
        }

       // label->setDestination();
      //  Updater::getInstance()->addJumpLabel(label);
        choiceLabels.push_back(label);
    }
    m_settingWidget->initChoiceWidget(title2,choiceLabels,choiceIcon);

    // 至此，我们就成功地将JSON文件中的内容读取到对应的临时数据中了。



}


 void JSReader::readJsonFileToReadAndSave()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open file error!";
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(data, &jsonError);

    if (jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "Json parse error:" << jsonError.errorString();
        return;
    }

    QJsonObject obj = document.object();

    // 读取 ChoiceLabelImage 字段
    if (obj.contains("ChoiceLabelImage") && obj["ChoiceLabelImage"].isString())
    {
        QString choiceLabelImage = obj["ChoiceLabelImage"].toString();
        // 将数据存入相关变量中
        // ...
        QImage imgLeft;
        imgLeft.load(choiceLabelImage);
        QImage imgRight = imgLeft.mirrored(true,false);

        m_rsWidget->initChoiceLabels(imgLeft,imgRight);

    }
      if (obj.contains("AchAddLabelNormal") && obj["AchAddLabelNormal"].isString())
    {
        QString addLabel1=obj["AchAddLabelNormal"].toString();
        QString addLabel2=obj["AchAddLabelPress"].toString();
        m_rsWidget->initAddLabel(addLabel1,addLabel2);
    }
      if (obj.contains("BackgroundPix") && obj["BackgroundPix"].isString())
      {
        QString backgroundPix=obj["BackgroundPix"].toString();
        m_rsWidget->initBackground(backgroundPix);
      }



    QString achMainShowLabelPix;
    // 读取 AchMainShowLabelPix 字段
    if (obj.contains("AchMainShowLabelPix") && obj["AchMainShowLabelPix"].isString())
    {
         achMainShowLabelPix= obj["AchMainShowLabelPix"].toString();
        // 将数据存入相关变量中
        // ...     
    }

    QString achReadNormal;
    // 读取 AchReadNormal 字段
    if (obj.contains("AchReadNormal") && obj["AchReadNormal"].isString())
    {
         achReadNormal= obj["AchReadNormal"].toString();
        // 将数据存入相关变量中
        // ...
    }

    QString achReadPress;
    // 读取 AchReadPress 字段
    if (obj.contains("AchReadPress") && obj["AchReadPress"].isString())
    {
        achReadPress= obj["AchReadPress"].toString();
        // 将数据存入相关变量中
        // ...
    }

    QString achSaveNormal;
    // 读取 AchSaveNormal 字段
    if (obj.contains("AchSaveNormal") && obj["AchSaveNormal"].isString())
    {
         achSaveNormal = obj["AchSaveNormal"].toString();
        // 将数据存入相关变量中
        // ...
    }

    QString achSavePress ;
    // 读取 AchSavePress 字段
    if (obj.contains("AchSavePress") && obj["AchSavePress"].isString())
    {
        achSavePress= obj["AchSavePress"].toString();
        // 将数据存入相关变量中
        // ...
    }

    QJsonArray achievementWidgetGroup=obj.value("Achievement").toArray();
    QVector<chievementWidget*> achWidgets;
    for(int i=0;i<achievementWidgetGroup.size();++i)
    {
        QJsonObject widgetObject=achievementWidgetGroup[i].toObject();
        chievementWidget* ach=new chievementWidget();

        QString ID=widgetObject.value("ID").toString();
        QString Path=widgetObject.value("Path").toString();
        QString CreateTime=widgetObject.value("CreateTime").toString();
        QString UpdateTime=widgetObject.value("UpdateTime").toString();
        QString StroyProgress=widgetObject.value("StroyProgress").toString();
        QString GameLevel=widgetObject.value("GameLevel").toString();
        QString Emblem1=widgetObject.value("Emblem1").toString();
        QString Emblem2=widgetObject.value("Emblem2").toString();
        QString Emblem3=widgetObject.value("Emblem3").toString();
        ach->initCenterLabel(achMainShowLabelPix);
        ach->initRSLabel(achReadNormal,achReadPress,achSaveNormal,achSavePress);
        //qDebug()<<"23333333333333";
        QString achInfo=QString("创建时间:"+CreateTime);
                achInfo+="\n";
                achInfo+=QString("更新时间:"+UpdateTime);

        ach->initAchInfo(achInfo);

        ach->initRecallInfo(ID,StroyProgress,GameLevel);

        QVector<QString> emblems;
        QVector<QString> emblemsPath;
        emblems<<Emblem1<<Emblem2<<Emblem3;
        for(int i=0;i<3;i++)
        {
            emblemsPath<<m_sourceTable->findEmblemTablePath(emblems[i]);
        }
        ach->initEmblems(emblemsPath);

        m_rsWidget->addAchWidget(ach);
    }


}

void JSReader::readJsonFileToMainWidget()
{
    QFile jsonFile(m_filePath);
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<Qt::endl;
        return;
    }

    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);

    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug()<<"Json Error!";
        return;
    }

    QJsonObject rootObj = jsonDoc.object();

    // 读取mainShowLabel
    QVector<JumpLabel*>mainShowLabelGroup;
    QVector<QRect>rectGroup;
    QJsonArray mainShowArr = rootObj.value("mainShowLabel").toArray();
    for(int i = 0; i < mainShowArr.size(); ++i)
    {
        JumpLabel * tmpJL=new JumpLabel();

        QJsonObject mainObj = mainShowArr.at(i).toObject();
        QString text = mainObj.value("Text").toString();
        QString pixPath = mainObj.value("Pix").toString();
        QRect rect = QRect(mainObj["Rect"].toArray()[0].toInt(),
                           mainObj["Rect"].toArray()[1].toInt(),
                           mainObj["Rect"].toArray()[2].toInt(),
                           mainObj["Rect"].toArray()[3].toInt());
        // 使用读取到的信息进行相关操作
        tmpJL->setText(text);
        QPixmap* pix=new QPixmap(pixPath);
        tmpJL->setPixmapPathGroup(pixPath,pixPath);
        tmpJL->setPixmapGroup(pix,pix);

        tmpJL->setMaskStatus(true);

        tmpJL->setAlignment(Qt::AlignCenter);

        tmpJL->setFont(QFont("楷体",30,QFont::Bold,Qt::white));
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
        tmpJL->setPalette(pa);

        tmpJL->setDestination(Updater::getInstance()->findWidget(text));
        connect(tmpJL, SIGNAL(jump(QWidget*)),
                Updater::getInstance()->findParent(Updater::getInstance()->findWidget(text)),SLOT(setCurrentWidget(QWidget*)));

        rectGroup<<rect;
        mainShowLabelGroup<<tmpJL;
    }
    m_mainWidget->initMainShowLabel(mainShowLabelGroup,rectGroup);



    //暂时未作

    // 读取ToolShowLabel
    QVector<JumpLabel*>toolLabelGroup;
    QVector<QRect> rectList;
    QJsonArray toolShowArr = rootObj.value("ToolShowLabel").toArray();
    for(int i = 0; i < toolShowArr.size(); ++i)
    {
        QJsonObject toolObj = toolShowArr.at(i).toObject();
        QString text=toolObj.value("Text").toString();
        QString pixPath = toolObj.value("Pix").toString();
        QRect rect = QRect(toolObj["Rect"].toArray()[0].toInt(),
                           toolObj["Rect"].toArray()[1].toInt(),
                           toolObj["Rect"].toArray()[2].toInt(),
                           toolObj["Rect"].toArray()[3].toInt());
        // 使用读取到的信息进行相关操作
        // ...

        JumpLabel * tmpL=new JumpLabel();
        tmpL->setPixmapPathGroup(pixPath,pixPath);
        tmpL->setPixmapGroup(new QPixmap(pixPath),new QPixmap(pixPath));

        connect(    tmpL,SIGNAL(jump(QWidget*)),
                    Updater::getInstance()->findParent(Updater::getInstance()->findWidget(text)), SLOT(setCurrentWidget(QWidget*))
                );

        toolLabelGroup<<tmpL;
        rectList<<rect;
    }
    m_mainWidget->initToolShowLabel(toolLabelGroup,rectList);



    // 读取ToolShowButton
    QJsonObject toolBtnObj = rootObj.value("ToolShowButton").toObject();
    QString pix1Path = toolBtnObj.value("Pix1").toString();
    QString pix2Path = toolBtnObj.value("Pix2").toString();
    // 使用读取到的信息进行相关操作
    // ...
    m_mainWidget->initToolButton(QPixmap(pix1Path),pix1Path,pix2Path);




    // 读取HeadWidget
    QJsonObject headWidgetObj = rootObj.value("HeadWidget").toObject();
    QString headPixPath = headWidgetObj.value("headPix").toString();
    QString headInfoPixPath = headWidgetObj.value("headInfoPix").toString();
    QString headFramePath = headWidgetObj.value("headFrame").toString();
    // 使用读取到的信息进行相关操作
    // ...
    HeadWidget * headW=new HeadWidget();
    QPixmap * head=new QPixmap(headPixPath);
    QPixmap * headInfo=new QPixmap(headInfoPixPath);
    headW->initPix(head,headInfo);
    QPixmap * headFrame=new QPixmap(headFramePath);
    headW->setFrame(headFrame);

    // 读取HeadWidgetRect
    QJsonArray headWidgetRectArr = rootObj.value("HeadWidgetRect").toArray();
    QRect headWidgetRect = QRect(headWidgetRectArr[0].toInt(),
                                 headWidgetRectArr[1].toInt(),
                                 headWidgetRectArr[2].toInt(),
                                 headWidgetRectArr[3].toInt());
    // 使用读取到的信息进行相关操作
    // ...
    QJsonObject tachieLabelObj = rootObj.value("TachieLabel").toObject();
    QString characterName=tachieLabelObj.value("CharacterName").toString();
    Character * tmpCharacter=m_characterHub->findCharacter(characterName);


    QRect tachieRect = QRect(rootObj["TachieRect"].toArray()[0].toInt(),
                       rootObj["TachieRect"].toArray()[1].toInt(),
                       rootObj["TachieRect"].toArray()[2].toInt(),
                       rootObj["TachieRect"].toArray()[3].toInt());

    TachieLabel *tachieLabel=new TachieLabel();
    tachieLabel->setTouchLock(true);
    tachieLabel->initCharacter(tmpCharacter,tachieRect);


    QMap<QString,QRect> touchRect;
    touchRect.insert("开心",QRect(tachieRect.x(),0,625,200));
    touchRect.insert("害羞",QRect(tachieRect.x(),(tachieRect.height())/4,tachieRect.width(),(tachieRect.height())/4));
    touchRect.insert("生气",QRect(tachieRect.x(),(tachieRect.height()*2)/4,tachieRect.width(),(tachieRect.height())/4));
    touchRect.insert("沮丧",QRect(tachieRect.x(),(tachieRect.height()*3)/4,tachieRect.width(),(tachieRect.height())/4));
    tachieLabel->initTouchRect(touchRect);
    tachieLabel->setVisible(true);
    m_mainWidget->initTachieLabel(tachieLabel,tachieRect);

    m_mainWidget->setHeadWidget(headW,headWidgetRect);



    // 读取BackgroundPix
    QString backgroundPixPath = rootObj.value("BackgroundPix").toString();
    // 使用读取到的信息进行相关操作
    // ...
    m_mainWidget->setBackground(backgroundPixPath);



}

void JSReader::readJsonFileToCharacterWidget()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        // 打开文件失败
        qDebug()<<"HHHHHHHHHHHHHHHHHH0";
        return;
    }

    QByteArray data = file.readAll();
    QJsonParseError error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &error));
    if (jsonDoc.isNull() || !jsonDoc.isObject())
    {
        // 解析 JSON 失败
        qDebug()<<"HHHHHHHHHHHHHHHHHH1";
        return;
    }

    QJsonObject rootObj = jsonDoc.object();
    if (!rootObj.contains("CharacterWidget"))
    {

        // 不包含 CharacterWidget 节点
        for(auto it:rootObj)
        {
            qDebug()<<it;
        }
        qDebug()<<"HHHHHHHHHHHHHHHHHH2";
        return;
    }

    QJsonObject charaWidgetObj = rootObj.value("CharacterWidget").toObject();
    if (!charaWidgetObj.contains("CharacterHubWidget")
        || !charaWidgetObj.contains("CharacterShowWidget")
        || !charaWidgetObj.contains("CharacterInfoWidget")
        || !charaWidgetObj.contains("BackgroundImagePath"))
    {
        // CharacterWidget 节点不完整
        qDebug()<<"HHHHHHHHHHHHHHHHHH3";
        return;
    }

    // 读取 CharacterHubWidget 节点
    QJsonObject charaHubWidgetObj = charaWidgetObj.value("CharacterHubWidget").toObject();
    if (!charaHubWidgetObj.contains("ShowRect")
        || !charaHubWidgetObj.contains("HideRect")
        || !charaHubWidgetObj.contains("AreaShowRect")
        || !charaHubWidgetObj.contains("AreaHideRect")
        || !charaHubWidgetObj.contains("CardSize")
        || !charaHubWidgetObj.contains("CardSmallSize")
        || !charaHubWidgetObj.contains("space"))
    {
        qDebug()<<"HHHHHHHHHHHHHHHHHH4";
        // CharacterHubWidget 节点不完整
        return;
    }
    //qDebug()<<"HHHHHHHHHHHHHHHHHHW";
    QRect showRect(charaHubWidgetObj.value("ShowRect").toArray().at(0).toInt(),
                   charaHubWidgetObj.value("ShowRect").toArray().at(1).toInt(),
                   charaHubWidgetObj.value("ShowRect").toArray().at(2).toInt(),
                   charaHubWidgetObj.value("ShowRect").toArray().at(3).toInt());
    QRect hideRect(charaHubWidgetObj.value("HideRect").toArray().at(0).toInt(),
                   charaHubWidgetObj.value("HideRect").toArray().at(1).toInt(),
                   charaHubWidgetObj.value("HideRect").toArray().at(2).toInt(),
                   charaHubWidgetObj.value("HideRect").toArray().at(3).toInt());
    QRect areaShowRect(charaHubWidgetObj.value("AreaShowRect").toArray().at(0).toInt(),
                       charaHubWidgetObj.value("AreaShowRect").toArray().at(1).toInt(),
                       charaHubWidgetObj.value("AreaShowRect").toArray().at(2).toInt(),
                       charaHubWidgetObj.value("AreaShowRect").toArray().at(3).toInt());
    QRect areaHideRect(charaHubWidgetObj.value("AreaHideRect").toArray().at(0).toInt(),
                       charaHubWidgetObj.value("AreaHideRect").toArray().at(1).toInt(),
                       charaHubWidgetObj.value("AreaHideRect").toArray().at(2).toInt(),
                       charaHubWidgetObj.value("AreaHideRect").toArray().at(3).toInt());
    QSize cardSize(charaHubWidgetObj.value("CardSize").toArray().at(0).toInt(),
                   charaHubWidgetObj.value("CardSize").toArray().at(1).toInt());
    QSize cardSmallSize(charaHubWidgetObj.value("CardSmallSize").toArray().at(0).toInt(),
                        charaHubWidgetObj.value("CardSmallSize").toArray().at(1).toInt());
    int space = charaHubWidgetObj.value("space").toInt();

    // 读取 CharacterShowWidget 节点
    QJsonObject charaShowWidgetObj = charaWidgetObj.value("CharacterShowWidget").toObject();
    if (!charaShowWidgetObj.contains("Rect"))
    {
        // CharacterShowWidget 节点不完整
        return;
    }
    QRect charaShowRect(charaShowWidgetObj.value("Rect").toArray().at(0).toInt(),
                        charaShowWidgetObj.value("Rect").toArray().at(1).toInt(),
                        charaShowWidgetObj.value("Rect").toArray().at(2).toInt(),
                        charaShowWidgetObj.value("Rect").toArray().at(3).toInt());

    // 读取 CharacterInfoWidget 节点
    QJsonObject charaInfoWidgetObj = charaWidgetObj.value("CharacterInfoWidget").toObject();
    if (!charaInfoWidgetObj.contains("LabelInfo")
        || !charaInfoWidgetObj.contains("LabelRect")
        || !charaInfoWidgetObj.contains("Space")
        || !charaInfoWidgetObj.contains("NormalPixPath")
        || !charaInfoWidgetObj.contains("ChoicePixPath"))
    {
        // CharacterInfoWidget 节点不完整
        return;
    }
    QJsonArray labelInfoArray = charaInfoWidgetObj.value("LabelInfo").toArray();
    QVector<JumpLabel *> characterInfoGroup;
    for (int i = 0; i < labelInfoArray.size(); i++)
    {
        QJsonObject labelInfoObj = labelInfoArray.at(i).toObject();
        QString text = labelInfoObj.value("Text").toString();
        QString type = labelInfoObj.value("Type").toString();
        JumpLabel * label = new JumpLabel();
        characterInfoGroup.append(label);
        label->setFont(QFont("楷体",25,QFont::Bold,Qt::white));
        label->setAlignment(Qt::AlignCenter);
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
        label->setPalette(pa);
        label->setText(text);

    }
    QRect labelRect(charaInfoWidgetObj.value("LabelRect").toArray().at(0).toInt(),
                    charaInfoWidgetObj.value("LabelRect").toArray().at(1).toInt(),
                    charaInfoWidgetObj.value("LabelRect").toArray().at(2).toInt(),
                    charaInfoWidgetObj.value("LabelRect").toArray().at(3).toInt());
    int infoSpace = charaInfoWidgetObj.value("Space").toInt();
    QString normalPixPath = charaInfoWidgetObj.value("NormalPixPath").toString();
    QString choicePixPath = charaInfoWidgetObj.value("ChoicePixPath").toString();

    for(auto it:characterInfoGroup)
    {
        it->setPixmapPathGroup(normalPixPath,choicePixPath);
    }



    // 读取 BackgroundImagePath 节点
    QString bkgPath = charaWidgetObj.value("BackgroundImagePath").toString();

    // 初始化 CharacterWidget

    CharacterHubWidget *characterHubWidget=new CharacterHubWidget(m_characterWidget);
    connect(characterHubWidget,&CharacterHubWidget::characterClicked,m_characterWidget,&CharacterWidget::setNowCharacter);
    characterHubWidget->initRect(showRect,hideRect);
    characterHubWidget->initCardSize(cardSize,cardSmallSize);
    characterHubWidget->initAreaRect(areaShowRect,areaHideRect);
    characterHubWidget->setSpace(space);
    characterHubWidget->initCharacterHub();
    connect(characterHubWidget,&CharacterHubWidget::widgetHide,m_characterWidget,&CharacterWidget::hubHide);
    connect(characterHubWidget,&CharacterHubWidget::widgetShow,m_characterWidget,&CharacterWidget::hubShow);


   // characterHubWidget->initWidget();
    m_characterWidget->initCharacterHubWidget(characterHubWidget,showRect);

    m_characterWidget->initCharacterInfoGroup(characterInfoGroup, labelRect, infoSpace);

    m_characterWidget->initCharacterInfoShowWidget(CharacterInfoShowWidget::getInstance(), charaShowRect);
    m_characterWidget->initCharacterStoryWidget(CharacterStoryShowWidget::getInstance(),charaShowRect);
    m_characterWidget->setBackground(bkgPath);

    m_characterWidget->initLink();



}

void JSReader::readJsonFileToStory()
{

    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray jsonData = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));

    if (!jsonDoc.isNull())
    {

        QVector<Story*> stL;

        QJsonObject topLevelObj = jsonDoc.object();

        if (topLevelObj.contains("StoryChapter"))
        {
            QJsonArray chapterArray = topLevelObj["StoryChapter"].toArray();
            for (int i=0; i<chapterArray.size(); ++i)
            {
                QJsonObject chapterObj = chapterArray[i].toObject();

                QString title = chapterObj["Title"].toString();
                QString storyIntroduction = chapterObj["StoryIntroduction"].toString();
                QString storyText = chapterObj["StoryText"].toString();
                QString storyCoverPix = chapterObj["StoryCoverPix"].toString();
                int linkCharacterID=chapterObj["CharacterID"].toInt();
                int linkStoryIdx = chapterObj["LinkStoryIdx"].toInt();

                // TODO: 对每个章节进行处理，这里只输出到控制台
                qDebug() << "Title:" << title
                         << ", StoryIntroduction:" << storyIntroduction
                         << ", StoryText:" << storyText
                         << ", StoryCoverPix:" << storyCoverPix
                         << ", LinkStoryIdx:" << linkStoryIdx;
                Story *story =new Story();
                story->initStory(linkStoryIdx,title,storyIntroduction,storyText);
                story->setCharacterID(linkCharacterID);
                story->setCoverPixUrl(storyCoverPix);
                stL<<story;
            }

        }
        m_characterHub->initStory(stL);
    }






}

// 读取JSON文件
void readJsonFile(const QString& fileName, StoryShowWidgetInfo& storyShowWidgetInfo) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 打开文件失败
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError || jsonDoc.isNull() || !jsonDoc.isObject()) {
        // 解析JSON失败
        return;
    }

    const QJsonObject& jsonObj = jsonDoc.object();
    const QJsonObject& storyShowWidgetObj = jsonObj.value("StoryShowWidget").toObject();

    // 解析ChoiceWidget信息
    if (storyShowWidgetObj.contains("ChoiceWidget")) {
        const QJsonObject& choiceWidgetObj = storyShowWidgetObj.value("ChoiceWidget").toObject();

        storyShowWidgetInfo.choiceWidgetInfo.widgetClass = choiceWidgetObj.value("WidgetClass").toString();

        const QJsonArray& widgetRectArray = choiceWidgetObj.value("WidgetRect").toArray();
        storyShowWidgetInfo.choiceWidgetInfo.rect.left = widgetRectArray.at(0).toInt();
        storyShowWidgetInfo.choiceWidgetInfo.rect.top = widgetRectArray.at(1).toInt();
        storyShowWidgetInfo.choiceWidgetInfo.rect.width = widgetRectArray.at(2).toInt();
        storyShowWidgetInfo.choiceWidgetInfo.rect.height = widgetRectArray.at(3).toInt();

        const QJsonObject& widgetSettingObj = choiceWidgetObj.value("WidgetSetting").toObject();
        const QJsonArray& labelArray = widgetSettingObj.value("Label").toArray();

        for (const auto& labelValue : labelArray) {
            if (labelValue.isObject()) {
                const QJsonObject& labelObj = labelValue.toObject();
                const QString& labelName = labelObj.value("LabelName").toString();
                storyShowWidgetInfo.choiceWidgetInfo.setting.labelNames << labelName;

                LabelInfo labelInfo;
                labelInfo.labelName = labelName;
                labelInfo.labelClass = labelObj.value("LabelClass").toString();

                const QJsonArray& labelGroupArray = labelObj.value("LabelGroup").toArray();
                for (const auto& groupValue : labelGroupArray) {
                    if (groupValue.isObject()) {
                        const QJsonObject& groupObj = groupValue.toObject();
                        LabelGroup labelGroup;
                        labelGroup.text = groupObj.value("Text").toString();
                        labelGroup.pix.pixUrl = groupObj.value("PixUrl").toString();
                        labelGroup.pix.status1 = groupObj.value("Status1").toString();
                        labelGroup.pix.status2 = groupObj.value("Status2").toString();
                        labelGroup.pix.status3 = groupObj.value("Status3").toString();
                        const QJsonArray& rectArray = groupObj.value("Rect").toArray();
                        labelGroup.rect.left = rectArray.at(0).toInt();
                        labelGroup.rect.top = rectArray.at(1).toInt();
                        labelGroup.rect.width = rectArray.at(2).toInt();
                        labelGroup.rect.height = rectArray.at(3).toInt();
                        labelGroup.mask = groupObj.value("Mask").toBool();
                        labelGroup.cardId = groupObj.value("CardID").toInt();
                        labelGroup.destination = groupObj.value("Destination").toString();
                        labelInfo.labelGroups << labelGroup;
                    }
                }

                // TODO：根据需求将Label信息存储到数据对象中
               // ChoiceWidget * tmpChoiceWidget=new ChoiceWidget();
                //tmpChoiceWidget->setParent(m_carouselWidget);






            }
        }














    }

    // 解析CarouselMapWidget信息
    if (storyShowWidgetObj.contains("CarousMapWidget")) {
        const QJsonObject& carousMapWidgetObj = storyShowWidgetObj.value("CarousMapWidget").toObject();

        storyShowWidgetInfo.carousMapWidgetInfo.widgetClass = carousMapWidgetObj.value("WidgetClass").toString();

        const QJsonArray& widgetRectArray = carousMapWidgetObj.value("WidgetRect").toArray();
        storyShowWidgetInfo.carousMapWidgetInfo.rect.left = widgetRectArray.at(0).toInt();
        storyShowWidgetInfo.carousMapWidgetInfo.rect.top = widgetRectArray.at(1).toInt();
        storyShowWidgetInfo.carousMapWidgetInfo.rect.width = widgetRectArray.at(2).toInt();
        storyShowWidgetInfo.carousMapWidgetInfo.rect.height = widgetRectArray.at(3).toInt();

        const QJsonObject& widgetSettingObj = carousMapWidgetObj.value("WidgetSetting").toObject();
        const QJsonArray& labelArray = widgetSettingObj.value("Label").toArray();

        for (const auto& labelValue : labelArray) {
            if (labelValue.isObject()) {
                const QJsonObject& labelObj = labelValue.toObject();
                const QString& labelName = labelObj.value("LabelName").toString();
                storyShowWidgetInfo.carousMapWidgetInfo.setting.labelNames << labelName;

                LabelInfo labelInfo;
                labelInfo.labelName = labelName;
                labelInfo.labelClass = labelObj.value("LabelClass").toString();

                const QJsonArray& labelGroupArray = labelObj.value("LabelGroup").toArray();
                for (const auto& groupValue : labelGroupArray) {
                    if (groupValue.isObject()) {
                        const QJsonObject& groupObj = groupValue.toObject();
                        LabelGroup labelGroup;
                        labelGroup.mask = groupObj.value("Mask").toBool();
                        labelGroup.cardId = groupObj.value("CardID").toInt();
                        labelGroup.destination = groupObj.value("Destination").toString();
                        labelInfo.labelGroups << labelGroup;
                    }
                }

                // TODO：根据需求将Label信息存储到数据对象中
            }
        }

        const QJsonObject& buttonObj = widgetSettingObj.value("Button").toObject();
        const QString& buttonName = buttonObj.value("ButtonName").toString();
        storyShowWidgetInfo.carousMapWidgetInfo.setting.buttonNames << buttonName;

        ButtonInfo buttonInfo;
        buttonInfo.buttonName = buttonName;
        buttonInfo.buttonClass = buttonObj.value("ButtonClass").toString();

        const QJsonArray& buttonGroupArray = buttonObj.value("ButtonGroup").toArray();
        for (const auto& groupValue : buttonGroupArray) {
            if (groupValue.isObject()) {
                const QJsonObject& groupObj = groupValue.toObject();
                ButtonGroup buttonGroup;
                buttonGroup.pressPix.pixUrl = groupObj.value("PressPixUrl").toString();
                buttonGroup.pressPix.status1 = groupObj.value("Status1").toString();
                buttonGroup.pressPix.status2 = groupObj.value("Status2").toString();
                buttonGroup.pressPix.status3 = groupObj.value("Status3").toString();
                buttonGroup.normalPix.pixUrl = groupObj.value("NormalPixUrl").toString();
                buttonGroup.normalPix.status1 = groupObj.value("Status1").toString();
                buttonGroup.normalPix.status2 = groupObj.value("Status2").toString();
                buttonGroup.normalPix.status3 = groupObj.value("Status3").toString();
                const QJsonArray& rectArray = groupObj.value("Rect").toArray();
                buttonGroup.rect.left = rectArray.at(0).toInt();
                buttonGroup.rect.top = rectArray.at(1).toInt();
                buttonGroup.rect.width = rectArray.at(2).toInt();
                buttonGroup.rect.height = rectArray.at(3).toInt();
                buttonGroup.link = groupObj.value("Link").toString();
                buttonInfo.buttonGroups << buttonGroup;
            }
        }

        // TODO：根据需求将Button信息存储到数据对象中
    }

    // 解析StoryInfoWidget信息
    if (storyShowWidgetObj.contains("StroyInfoWidget")) {
        const QJsonObject& storyInfoWidgetObj = storyShowWidgetObj.value("StroyInfoWidget").toObject();

        storyShowWidgetInfo.storyInfoWidgetInfo.widgetClass = storyInfoWidgetObj.value("WidgetClass").toString();

        const QJsonArray& widgetRectArray = storyInfoWidgetObj.value("WidgetRect").toArray();
        storyShowWidgetInfo.storyInfoWidgetInfo.rect.left = widgetRectArray.at(0).toInt();
        storyShowWidgetInfo.storyInfoWidgetInfo.rect.top = widgetRectArray.at(1).toInt();
        storyShowWidgetInfo.storyInfoWidgetInfo.rect.width = widgetRectArray.at(2).toInt();
        storyShowWidgetInfo.storyInfoWidgetInfo.rect.height = widgetRectArray.at(3).toInt();

        const QJsonObject& widgetSettingObj = storyInfoWidgetObj.value("WidgetSetting").toObject();
        const QJsonArray& linkObjectsArray = widgetSettingObj.value("LinkObjects").toArray();
        QStringList linkObjectsList;
        for (int i = 0; i < linkObjectsArray.size(); ++i) {
            linkObjectsList.append(linkObjectsArray.at(i).toString());
        }
        const QJsonArray& linkSignalsArray = widgetSettingObj.value("LinkSignals").toArray();
        QStringList linkSignalsList;
        for (int i = 0; i < linkSignalsArray.size(); ++i) {
            linkSignalsList.append(linkSignalsArray.at(i).toString());
        }
        const QJsonArray& linkSlotsArray = widgetSettingObj.value("LinkSlots").toArray();
        QStringList linkSlotsList;
        for (int i = 0; i < linkSlotsArray.size(); ++i) {
            linkSlotsList.append(linkSlotsArray.at(i).toString());
        }

        if (!linkObjectsList.isEmpty() && !linkSignalsList.isEmpty() && !linkSlotsList.isEmpty()) {
            storyShowWidgetInfo.storyInfoWidgetInfo.link.linkObjectName = linkObjectsList.first();
            storyShowWidgetInfo.storyInfoWidgetInfo.link.linkSignalName = linkSignalsList.first();
            storyShowWidgetInfo.storyInfoWidgetInfo.link.linkSlotName = linkSlotsList.first();
        }

        const QJsonObject& labelObj = widgetSettingObj.value("Label").toObject();
        const QString& labelName = labelObj.value("LabelName").toString();
        storyShowWidgetInfo.storyInfoWidgetInfo.setting.labelNames << labelName;

        LabelInfo labelInfo;
        labelInfo.labelName = labelName;
        labelInfo.labelClass = labelObj.value("LabelClass").toString();

        const QJsonArray& labelGroupArray = labelObj.value("LabelGroup").toArray();
        for (const auto& groupValue : labelGroupArray) {
            if (groupValue.isObject()) {
                const QJsonObject& groupObj = groupValue.toObject();
                LabelGroup labelGroup;
                labelGroup.text = groupObj.value("Text").toString();
                labelGroup.pix.pixUrl = groupObj.value("PixUrl").toString();
                labelGroup.pix.status1 = groupObj.value("Status1").toString();
                labelGroup.pix.status2 = groupObj.value("Status2").toString();
                labelGroup.pix.status3 = groupObj.value("Status3").toString();
                const QJsonArray& rectArray = groupObj.value("Rect").toArray();
                labelGroup.rect.left = rectArray.at(0).toInt();
                labelGroup.rect.top = rectArray.at(1).toInt();
                labelGroup.rect.width = rectArray.at(2).toInt();
                labelGroup.rect.height = rectArray.at(3).toInt();
                labelGroup.mask = groupObj.value("Mask").toBool();
                labelGroup.cardId = groupObj.value("CardID").toInt();
                labelGroup.destination = groupObj.value("Destination").toString();
                labelInfo.labelGroups << labelGroup;
            }
        }

        // TODO：根据需求将Label信息存储到数据对象中
    }
}


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
    m_settingWidget=SettingWidget::getInstance();
    m_rsWidget=RSWidget::getInstance();
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
    // 获取/设置标签文本样式1
    QString labelTextStyle1 = jsonObj.value("Label_text_style1").toString();
    styleDic.insert("Label_text_style1", labelTextStyle1);

    // 获取/设置标签文本样式2
    QString labelTextStyle2 = jsonObj.value("Label_text_style2").toString();
    styleDic.insert("Label_text_style2", labelTextStyle2);

    // 获取/设置标签文本样式3
    QString labelTextStyle3 = jsonObj.value("Label_text_style3").toString();
    styleDic.insert("Label_text_style3", labelTextStyle3);

    qDebug()<<styleDic;
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
        qDebug()<<size;
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
    }

    // 读取 AchMainShowLabelPix 字段
    if (obj.contains("AchMainShowLabelPix") && obj["AchMainShowLabelPix"].isString())
    {
        QString achMainShowLabelPix = obj["AchMainShowLabelPix"].toString();
        // 将数据存入相关变量中
        // ...
    }

    // 读取 AchReadNormal 字段
    if (obj.contains("AchReadNormal") && obj["AchReadNormal"].isString())
    {
        QString achReadNormal = obj["AchReadNormal"].toString();
        // 将数据存入相关变量中
        // ...
    }

    // 读取 AchReadPress 字段
    if (obj.contains("AchReadPress") && obj["AchReadPress"].isString())
    {
        QString achReadPress = obj["AchReadPress"].toString();
        // 将数据存入相关变量中
        // ...
    }

    // 读取 AchSaveNormal 字段
    if (obj.contains("AchSaveNormal") && obj["AchSaveNormal"].isString())
    {
        QString achSaveNormal = obj["AchSaveNormal"].toString();
        // 将数据存入相关变量中
        // ...
    }

    // 读取 AchSavePress 字段
    if (obj.contains("AchSavePress") && obj["AchSavePress"].isString())
    {
        QString achSavePress = obj["AchSavePress"].toString();
        // 将数据存入相关变量中
        // ...
    }
}

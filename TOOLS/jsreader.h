#ifndef JSREADER_H
#define JSREADER_H


#include "updater.h"

#include "nowachievement.h"
#include "../Story/character.h"
#include "musicplayer.h"
#include "../UI/style.h"
#include "../UI/menuwidget.h"
#include "../UI/settingwidget.h"
#include "../UI/chievementwidget.h"
#include "../UI/rswidget.h"

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QSlider>



class JSReader : public QObject
{
    Q_OBJECT

public:
    // ... 省略其他函数 ...
    JSReader();
    void readJsonFileToAchievement();  //读取JSON文件内容到NowAchievement中
    void readJsonFileToMusicPlayer();  //读取JSON文件内容到MusicPlayer中
    void readJsonFileToStyle();
    void readJsonFileToMenuWidget();
    void readJsonFileToSetting();
    void readJsonFileToReadAndSave();
    QVector<Character*>readJsonFileToCharacter(); //读取JSON文件内容并返回



    void setFilePath(const QString &filePath);  //设置读取路径

    void init();



private:

    QString m_filePath;
    NowAchievement * m_achievement;
    MusicPlayer * m_musicPlayer;
    MenuWidget * m_menuWidget;
    SettingWidget * m_settingWidget;
    RSWidget * m_rsWidget;

signals:
    void deckInfoUpdated(const QVector<QVector<QString> >& deckInfo);

};

#endif // JSREADER_H

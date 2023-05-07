#ifndef JSREADER_H
#define JSREADER_H



#include "nowachievement.h"
#include "../Story/character.h"
#include "musicplayer.h"

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class JSReader : public QObject
{
    Q_OBJECT

public:
    // ... 省略其他函数 ...
    JSReader();
    void readJsonFileToAchievement();  //读取JSON文件内容到NowAchievement中
    void readJsonFileToMusicPlayer();  //读取JSON文件内容到MusicPlayer中
    QVector<Character*>readJsonFileToCharacter(); //读取JSON文件内容并返回



    void setFilePath(const QString &filePath);  //设置读取路径

    void init();



private:

    QString m_filePath;
    NowAchievement * m_achievement;
    MusicPlayer * m_musicPlayer;
signals:
    void deckInfoUpdated(const QVector<QVector<QString> >& deckInfo);

};

#endif // JSREADER_H

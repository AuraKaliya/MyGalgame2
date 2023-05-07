#ifndef JSSAVER_H
#define JSSAVER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>

#include <QDateTime>

#include "nowachievement.h"

class JSSaver : public QObject
{
    Q_OBJECT
public:
    explicit JSSaver(QObject *parent = nullptr);
    void saveAchievementToJsonFile();

    void init();
    void setFilePath(const QString &filePath);

private:
    QString m_filePath;
    NowAchievement* m_achievement;
signals:

};


#endif // JSSAVER_H

#ifndef CHIEVEMENTWIDGET_H
#define CHIEVEMENTWIDGET_H

#include <QWidget>
#include "jumplabel.h"
#include "../TOOLS/updater.h"
#include <QLabel>
#include <QPixmap>
#include <QString>

class chievementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit chievementWidget(QWidget *parent = nullptr);

    void initRSLabel(QString readNormal,QString readPress,QString saveNormal,QString savePress);
    void intiMainLabel(QString cen,QString achInfo,QVector<QString>emblem,QString achID,QString stP,QString gL);

private:
    JumpLabel *m_readLabel;
    JumpLabel *m_saveLabel;
    QLabel * m_centerLabel;

    QLabel * m_achInfoLaebl;
    QVector<QLabel*>m_emblems;
    QLabel * m_emblemLabel1;
    QLabel * m_emblemLabel2;
    QLabel * m_emblemLabel3;
    //存档ID 剧情进度 存档难度
    QVector<QLabel*>m_infoLabels;
    QLabel * m_achIDLabel;
    QLabel * m_storyProgressLabel;
    QLabel * m_gameLevelLabel;


signals:


};

#endif // CHIEVEMENTWIDGET_H

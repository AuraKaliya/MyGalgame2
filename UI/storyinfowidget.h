#ifndef STORYINFOWIDGET_H
#define STORYINFOWIDGET_H

#include <QWidget>
#include "tachielabel.h"
#include <QLabel>
#include <QScrollArea>
#include <QRect>
#include <QString>
#include "../DATA/Story/character.h"
#include "characterstoryshowwidget.h"


class StoryInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StoryInfoWidget(QWidget *parent = nullptr);
    void initTachie(Character* character,QRect rect);
    void initStory(QString storyTitle,QString storyIntroduction);
    void initStory();
public slots:
    void setNowStory(int);
signals:
private:

    TachieLabel * m_tachieLabel;
    QScrollArea * m_storyIntroArea;
    QWidget * m_storyIntroWidget;
    QLabel * m_storyHeadLabel;
    QLabel * m_slipLabel;
    QLabel * m_storyIntroLabel;
    Character* m_character;
    QString m_storyTitle;
    QString m_storyIntroduction;
    CharacterStoryShowWidget* m_characterStoryWidget;
};

#endif // STORYINFOWIDGET_H

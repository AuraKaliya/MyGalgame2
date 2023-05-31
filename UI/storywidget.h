#ifndef STORYWIDGET_H
#define STORYWIDGET_H

#include <QWidget>
#include <QMap>

#include "uiwidget.h"
#include "tachielabel.h"
#include "talkshowwidget.h"
#include "../DATA/Story/character.h"
#include "../DATA/Story/characterhub.h"
#include "../DATA/Story/story.h"

typedef void (*FuncP)(QString) ;

class StoryWidget : public UIWidget
{
    Q_OBJECT
public:
    static StoryWidget* getInstance(QWidget * parent=nullptr);

    void setBackgroundPixUrl(QString) override;
   void initTalkShowWidget(TalkShowWidget * talkShowWidget,QRect rect) override;
   void initTachieLabel(TachieLabel* tachieLabel,QRect rect) override;
   static void setNowCharacter(QString name);
   static void setNowCharacterGesture(QString gesUrl);
   static void setStory(Story*);
   static void startStory();


public slots:
    static void nextSegment();

private slots:
   static void solveOption(QString);
   static void solveTalkText(QString);
   static void solveBackground(QString);
   static void solveCharacter(QString);
   static void solveGesture(QString);
   static void solvePlusIntroduction(QString);
    // void showOption();
signals:
   void storyFinished();
private:
    static StoryWidget* m_instance;
    explicit StoryWidget(QWidget *parent = nullptr);
    static  QMap<QString,FuncP> m_textTypeGroup;

   static Character * m_nowCharacter;
   static Story * m_nowStory;
    //QStringList
   static QVector<QString> m_segmentGroup;
   static TachieLabel* m_talkerLabel;
   static TalkShowWidget * m_talkShowWidget;
   static  QPixmap* m_backgroundPix;
   static  int m_nowSegIdx;

};

#endif // STORYWIDGET_H

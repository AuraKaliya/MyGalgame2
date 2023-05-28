#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QRect>
#include <QMap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QStackedWidget>
#include <QRandomGenerator>

#include "characterhubwidget.h"
#include "JumpLabel.h"
#include "../DATA/Story/characterhub.h"
#include "characterinfoshowwidget.h"
#include "characterstoryshowwidget.h"

#include "style.h"

class CharacterWidget : public QWidget
{
    Q_OBJECT
public:
    static CharacterWidget* getInstance(QWidget *parent = nullptr);
    void initCharacterHubWidget(CharacterHubWidget * charaHubWidget,QRect rect);
    void initCharacterInfoGroup(QVector<JumpLabel*>characterInfoGroup,QRect InfoRect,int space=10);

    void initCharacterInfoShowWidget(CharacterInfoShowWidget* InfoShowWidget,QRect InfoShowRect);
    void initCharacterStoryWidget(CharacterStoryShowWidget* storyShowWidget,QRect InfoShowRect);
    void initLink();

    void setBackground(QString bkgPath);
   // void linkShowAndHide(QPushButton * showHubBtn,QPushButton * hideHubBtn);
    void paintEvent(QPaintEvent *e)override;
    void setNowCharacterGes(QString gestPath);
    void mousePressEvent(QMouseEvent *e) override;

public slots:
    void hubShow();
    void hubHide();
    void setNowCharacter(Character* ch);
    void OptionChanged(JumpLabel* jL);

private:
    CharacterWidget(QWidget *parent = nullptr);
    static CharacterWidget* instance;

    Character * m_nowCharacter;
    CharacterHub * m_hub;
    CharacterHubWidget * m_charaHubWidget;
    CharacterInfoShowWidget* m_infoShowWidget;
    CharacterStoryShowWidget* m_storyShowWidget;
    QScrollArea * m_storyArea;

    QVector<JumpLabel* >m_characterInfoGroup;


    QStackedWidget * m_characterDetailShowWidget;
    QVector<QWidget*>m_infoShowWidgetGroup;

    QPixmap *m_backgroundPix;

    QRect m_characterRect;
    QPixmap *m_characterTachie;

     QStringList linesKey = {"仇视", "陌生", "友好", "信赖", "爱恋"};
    QVector<QRect*> characterBodyRect;
    QRect*m_characterHeadRect;      //开心
    QRect*m_characterBraRect;       //害羞
    QRect*m_characterLegRect;       //生气
    QRect*m_characterFootRect;      //沮丧
    QMap<QRect*,QString>characterBodyReflect;

    JumpLabel* NowOptionLabel;

   // QPushButton * m_showHubBtn;
   // QPushButton * m_hideHubBtn;

    //QGridLayout * mainLayout;


signals:

};

#endif // CHARACTERWIDGET_H

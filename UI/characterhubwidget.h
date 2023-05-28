#ifndef CHARACTERHUBWIDGET_H
#define CHARACTERHUBWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QScrollArea>

#include <QMap>
#include <QVector>

#include "jumplabel.h"
#include "searchblok.h"
#include "slideblock.h"
#include "../DATA/Story/characterhub.h"
#include "characterinfoshowwidget.h"

class CharacterHubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterHubWidget(QWidget *parent = nullptr);
    void initCharacterHub();

    void initRect(QRect showRect,QRect hideRect);
    void initCardSize(QSize cardSize,QSize cardSmallSize);
    void initAreaRect(QRect showRect,QRect hideRect);

    void setSpace(int sp);
    void setbackground();


public slots:
    void hideWidget();
    void showWidget();
    void characterChoiced(int);


signals:
    void characterClicked(Character*);
    void widgetHide();
    void widgetShow();
private:
    Searchblok * m_searchBlock;
    SlideBlock * m_slideBlock;

    QScrollArea * m_characterShowArea;
    QWidget * m_characterShowWidget;
    QVector <JumpLabel*> m_characterLabelGroup;

    QRect m_showRect;
    QRect m_hideRect;
    QSize m_cardSize;
    QSize m_cardSmallSize;
    int m_space;



    QRect m_showAreaRect;
    QRect m_showWidgetRect;
    QRect m_hideWidgetRect;
    QRect m_hideAreaRect;


    QStackedLayout *m_stackedLayout;
    QGridLayout *m_showLayout;
    QGridLayout *m_hideLayout;


};

#endif // CHARACTERHUBWIDGET_H

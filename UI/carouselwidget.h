#ifndef CAROUSELWIDGET_H
#define CAROUSELWIDGET_H

#include <QWidget>
#include "carouselmapwidget.h"
#include "storyinfowidget.h"
#include "choicewidget.h"


class CarouselWidget : public QWidget
{
    Q_OBJECT

public:
    static CarouselWidget* getInstance(QWidget *parent = nullptr);
    CarouselMapWidget* mapWidget();
    void initMask(QMap<QLabel*,QRect>mask);
    void initCaroselMapWidget( CarouselMapWidget*mapWidget,QRect rect);
    void initStoryInfoWidget(StoryInfoWidget* stIW,QRect rect);
    void initChoiceWidget(ChoiceWidget* cw,QRect rect);

signals:

private:
    explicit CarouselWidget(QWidget *parent = nullptr);
    CarouselMapWidget* m_mapWidget;
    StoryInfoWidget* m_storyInfoWidget;
    ChoiceWidget* m_choiceWidget;
    QMap<QLabel*,QRect>m_maskGroup;
    static CarouselWidget* instance;
};

#endif // CAROUSELWIDGET_H

#ifndef CAROUSELWIDGET_H
#define CAROUSELWIDGET_H

#include <QWidget>
#include <QPainter>
#include "carouselmapwidget.h"
#include "storyinfowidget.h"
#include "choicewidget.h"
#include "../DATA/Story/characterhub.h"

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
    void initBackgroundPix(QString bkUrl);

    void initChoiced();

    void paintEvent(QPaintEvent* e) override;
    int getNowStoryIdx() const;

public slots:
    void characterChoiced(int);
    void storyChoiced(int);

signals:
    void joinStory(int);
private:
    explicit CarouselWidget(QWidget *parent = nullptr);
    int nowStoryIdx;
    CarouselMapWidget* m_mapWidget;
    StoryInfoWidget* m_storyInfoWidget;
    ChoiceWidget* m_choiceWidget;
    QPixmap* m_backgroundPix;
    QMap<QLabel*,QRect>m_maskGroup;
    static CarouselWidget* instance;
};

#endif // CAROUSELWIDGET_H

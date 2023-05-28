#ifndef CAROUSELMAPWIDGET_H
#define CAROUSELMAPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QParallelAnimationGroup>
#include <QString>
#include <QSize>
#include <QRect>

#include "jumplabel.h"

/*

用于轮播效果的窗体
需要做到：轮播部件的深度切换、部件的缩放和平移
需要有一个Vector


*/


/*
另一种实现方案：
列表直接排列设置当前scale和正常scale，

*/


class CarouselMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CarouselMapWidget(QWidget *parent = nullptr);
    void initCarousel(QVector<JumpLabel*> lbg,QSize curSize,QSize norSize,int margin=20);
    void initMask(QMap<QLabel*,QRect>mask);
    void initMaskTest();
    void initZ();
    void initTest();
    void addLabel(JumpLabel* lb);
public slots:
    void preLabel();
    void nextLabel();

signals:
    void nowStory(int);
private:
    QMap<QLabel*,QRect>m_maskGroup;
    QVector<JumpLabel*>m_carsouseLabelGroup;
    QPushButton * m_leftBtn;
    QPushButton * m_rightBtn;
    int m_preIdx;
    int m_currentIdx;
    int m_nextIdx;
    QSize m_currentSize;
    QSize m_normalSize;

    int m_margin;

    bool animationLock;

    QPropertyAnimation* m_animation;



};

#endif // CAROUSELMAPWIDGET_H

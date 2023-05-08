#ifndef RIPPLEEFFECT_H
#define RIPPLEEFFECT_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include<QPropertyAnimation>
#include <QString>
#include<QPropertyAnimation>

//GPT的想法很好，但是功能并不能实现，这个类由GPT生成，目前已废弃（等空了学习一下QPropertyAnimation），水波效果采用传统的单水波效果，实现在ripple类中。
class RippleEffect :public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    RippleEffect(QPointF center, QRgb color, qreal radius, QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override; // 重写鼠标点击事件处理函数
signals:
    void clicked(); // 自定义clicked信号

protected:


private:
    QPointF m_center;
    QRgb m_color;
    qreal m_radius;

public:

};

#endif // RIPPLEEFFECT_H

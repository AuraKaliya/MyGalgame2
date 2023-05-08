#include "rippleeffect.h"

#include <QPainter>
#include<QPropertyAnimation>

RippleEffect::RippleEffect(QPointF center, QRgb color, qreal radius, QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , m_center(center)
    , m_color(color)
    , m_radius(radius)
{
    setAcceptHoverEvents(true); // 开启鼠标事件响应
}
QRectF RippleEffect::boundingRect() const
{
    return QRectF(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2);
}

void RippleEffect::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing); // 开启抗锯齿
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(m_color));
    qreal opacity = 1.0; // 定义初始透明度
    for (int i = 0; i < 5; ++i) {
        painter->setOpacity(opacity); // 设置透明度
        painter->drawEllipse(m_center, m_radius * (i + 1) / 5.0, m_radius * (i + 1) / 5.0);
        opacity -= 0.2; // 透明度依次减小

    }
    QPropertyAnimation *animation = new QPropertyAnimation(this, "radius"); //创建QPropertyAnimation对象
    animation->setDuration(500); //设置动画持续时间

    animation->setStartValue(m_radius); // 设置动画起始值
    animation->setEndValue(m_radius * 2); // 设置动画结束值
    animation->start(); // 启动动画
}

void RippleEffect::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "radius"); //创建QPropertyAnimation对象
        animation->setDuration(350); //设置动画持续时间

        animation->setStartValue(m_radius); // 设置动画起始值
        animation->setEndValue(m_radius * 2); // 设置动画结束值

        animation->start(); // 启动动画

    }
}

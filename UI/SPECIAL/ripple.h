#ifndef RIPPLE_H
#define RIPPLE_H

#include <QWidget>
#include <QVariantAnimation>
#include <QPainter>
#include <QPainterPath>
#include <QPoint>
#include <QCursor>

#define RIPPLE_RADIUS 15

class Ripple : public QWidget
{
    Q_OBJECT
public:
    // 构造函数
    explicit Ripple(QWidget *parent = nullptr);

    // 重写QWidget的show方法
    void show();
    // 设置水滴颜色
    void setColor(QColor color);
    // 移动水滴到指定位置
    void move(const QPoint &point);

signals:
private slots:
    // 当水滴半径变化时，更新水滴的绘制
    void onRadiusChanged(QVariant value);

private:
    // 绘制水滴
    void paintEvent(QPaintEvent *event) override;

    // 水滴动画
    QVariantAnimation *m_rippleAnimation;
    // 水滴当前半径
    int m_radius;
    // 水滴中心位置
    QPointF m_point;
    // 水滴颜色
    QColor m_color;
    // 显示水滴的路径
    QPainterPath m_showRip;
    // 隐藏水滴的路径
    QPainterPath m_hideRip;
};

#endif // RIPPLE_H


#include "ripple.h"
#include "qpainter.h"

Ripple::Ripple(QWidget *parent)
    : QWidget{parent}
    , m_rippleAnimation(nullptr)
    , m_radius(0)
    , m_point(QCursor::pos())
    , m_color(QColor(255,120,0,255))
{
    // 初始化水滴大小和窗口属性
    setFixedSize(RIPPLE_RADIUS*2.5, RIPPLE_RADIUS*2.5);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::CustomizeWindowHint | Qt::Window);
    // 设置窗口背景为透明
    setAttribute(Qt::WA_TranslucentBackground);
    // 关闭窗口时自动删除对象
    setAttribute(Qt::WA_DeleteOnClose, true);

    m_rippleAnimation=new QVariantAnimation(this);
}

void Ripple::show()
{
    __super::show();
    // 启动水滴动画
    m_rippleAnimation->setStartValue(0);
    m_rippleAnimation->setEndValue(RIPPLE_RADIUS);
    m_rippleAnimation->setDuration(350);

    connect(m_rippleAnimation, &QVariantAnimation::valueChanged, this, &Ripple::onRadiusChanged);
    connect(m_rippleAnimation, &QVariantAnimation::finished, this, &Ripple::close);
    // 将水滴颜色的alpha通道设置为250
    m_color.setAlpha(250);
    m_rippleAnimation->start();
}

void Ripple::setColor(QColor color)
{
    m_color=color;
}

void Ripple::move(const QPoint &point)
{
    QPoint tp=point-QPoint(RIPPLE_RADIUS,RIPPLE_RADIUS);
    __super::move(tp);
}

void Ripple::onRadiusChanged(QVariant value)
{
    if (m_radius < RIPPLE_RADIUS)
    {
        // 水滴半径增加2像素
        m_radius += 2;
        // 设置颜色的alpha通道值，使水滴渐渐消失
        m_color.setAlpha(m_color.alpha() - 30);
        // 更新窗口绘制
        update();
    }
}

void Ripple::paintEvent(QPaintEvent *event)
{
    // 清空路径
    m_showRip.clear();
    m_hideRip.clear();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    painter.setBrush(QBrush(m_color));

    // 计算水滴显示和隐藏的路径
    m_showRip.addEllipse(QPoint(RIPPLE_RADIUS + 2, RIPPLE_RADIUS + 2), m_radius + 2, m_radius + 2);
    m_hideRip.addEllipse(QPoint(RIPPLE_RADIUS + 2, RIPPLE_RADIUS + 2), m_radius, m_radius);
    m_showRip -= m_hideRip;

    // 绘制水滴
    painter.drawPath(m_showRip);
}
